/*******************************************************************************
 * Copyright (c) 2009, 2013 Wind River Systems, Inc. and others.
 *
 * This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License 2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *     Doug Schaefer - initial API and implementation
 *     Liviu Ionescu - Arm version
 *     Liviu Ionescu - RISC-V version
 *******************************************************************************/

package org.eclipse.embedcdt.managedbuild.cross.riscv.core;

import java.io.File;

import org.eclipse.cdt.core.cdtvariables.CdtVariableException;
import org.eclipse.cdt.managedbuilder.core.IConfiguration;
import org.eclipse.cdt.managedbuilder.core.IOption;
import org.eclipse.cdt.managedbuilder.core.IToolChain;
import org.eclipse.cdt.managedbuilder.core.ManagedBuildManager;
import org.eclipse.cdt.managedbuilder.envvar.IBuildEnvironmentVariable;
import org.eclipse.cdt.managedbuilder.envvar.IConfigurationEnvironmentVariableSupplier;
import org.eclipse.cdt.managedbuilder.envvar.IEnvironmentVariableProvider;
import org.eclipse.cdt.managedbuilder.macros.IBuildMacroProvider;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.runtime.Platform;
import org.eclipse.embedcdt.core.EclipseUtils;
import org.eclipse.embedcdt.internal.managedbuild.cross.riscv.core.Activator;
import org.eclipse.embedcdt.managedbuild.cross.core.preferences.PersistentPreferences;

public class EnvironmentVariableSupplier implements IConfigurationEnvironmentVariableSupplier {

	// ------------------------------------------------------------------------

	private static boolean DEBUG_PATH = false;

	// ------------------------------------------------------------------------

	@Override
	public IBuildEnvironmentVariable getVariable(String variableName, IConfiguration configuration,
			IEnvironmentVariableProvider provider) {
		if (PathEnvironmentVariable.isVar(variableName)) {
			return PathEnvironmentVariable.create(configuration);
		} else {
			// System.out.println("getVariable(" + variableName + ","
			// + configuration.getName() + ") returns null");
			return null;
		}
	}

	@Override
	public IBuildEnvironmentVariable[] getVariables(IConfiguration configuration,
			IEnvironmentVariableProvider provider) {
		IBuildEnvironmentVariable path = PathEnvironmentVariable.create(configuration);
		if (path != null) {
			return new IBuildEnvironmentVariable[] { path };
		} else {
			// System.out.println("getVariables(" + configuration.getName()
			// + ") returns empty array");
			return new IBuildEnvironmentVariable[0];
		}
	}

	private static class PathEnvironmentVariable implements IBuildEnvironmentVariable {

		public static String name = "PATH"; //$NON-NLS-1$

		private File path;

		private PathEnvironmentVariable(File path) {
			// System.out.println("cpath=" + path);
			this.path = path;
		}

		public static PathEnvironmentVariable create(IConfiguration configuration) {
			IToolChain toolchain = configuration.getToolChain();

			IProject project = (IProject) configuration.getManagedProject().getOwner();

			// Get the build tools path from the common store.
			PersistentPreferences commonPersistentPreferences = org.eclipse.embedcdt.internal.managedbuild.cross.core.Activator
					.getInstance().getPersistentPreferences();

			String path = commonPersistentPreferences.getBuildToolsPath(project);

			IOption option;
			option = toolchain.getOptionBySuperClassId(Option.OPTION_TOOLCHAIN_NAME); // $NON-NLS-1$
			String toolchainName = (String) option.getValue();

			String toolchainPath = null;

			// Get the toolchain path from this plug-in store.
			PersistentPreferences persistentPreferences = Activator.getInstance().getPersistentPreferences();
			// Get the most specific toolchain path (project, workspace,
			// Eclipse, defaults).
			toolchainPath = persistentPreferences.getToolchainPath(toolchainName, project);

			if (path.isEmpty()) {
				path = toolchainPath;
			} else {
				if (!toolchainPath.isEmpty()) {
					// Concatenate build tools path with toolchain path.
					path += EclipseUtils.getPathSeparator();
					path += toolchainPath;
				}
			}

			if (!path.isEmpty()) {

				// if present, substitute macros
				if (path.indexOf("${") >= 0) {
					path = resolveMacros(path, configuration);
				}

				File sysroot = new File(path);
				// File bin = new File(sysroot, "bin"); //$NON-NLS-1$
				// if (bin.isDirectory()) {
				// sysroot = bin;
				// }
				if (DEBUG_PATH) {
					if (Activator.getInstance().isDebugging()) {
						System.out.println("riscv.PathEnvironmentVariable.create() PATH=" + sysroot + " cfg="
								+ configuration + " prj=" + configuration.getManagedProject().getOwner().getName());
					}
				}
				return new PathEnvironmentVariable(sysroot);
			}

			// System.out.println("create(" + configuration.getName()
			// + ") returns null");
			return null;
		}

		private static String resolveMacros(String str, IConfiguration configuration) {

			String result = str;
			try {
				result = ManagedBuildManager.getBuildMacroProvider().resolveValue(str, "", " ", //$NON-NLS-1$ //$NON-NLS-2$
						IBuildMacroProvider.CONTEXT_CONFIGURATION, configuration);
			} catch (CdtVariableException e) {
				Activator.log("resolveMacros " + e.getMessage());
			}

			return result;

		}

		public static boolean isVar(String name) {
			// Windows has case insensitive env var names
			return Platform.getOS().equals(Platform.OS_WIN32) ? name.equalsIgnoreCase(PathEnvironmentVariable.name)
					: name.equals(PathEnvironmentVariable.name);
		}

		@Override
		public String getDelimiter() {
			return Platform.getOS().equals(Platform.OS_WIN32) ? ";" : ":"; //$NON-NLS-1$ //$NON-NLS-2$
		}

		@Override
		public String getName() {
			return name;
		}

		@Override
		public int getOperation() {
			return IBuildEnvironmentVariable.ENVVAR_PREPEND;
		}

		@Override
		public String getValue() {
			return path.getAbsolutePath();
		}

	}

	// ------------------------------------------------------------------------
}
