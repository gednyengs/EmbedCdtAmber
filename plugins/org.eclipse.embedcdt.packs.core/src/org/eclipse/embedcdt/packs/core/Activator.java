/*******************************************************************************
 * Copyright (c) 2014, 2020 Liviu Ionescu and others.
 *
 * This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License 2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 * 
 * Contributors:
 *     Liviu Ionescu - initial implementation.
 *     Alexander Fedorov (ArSysOp) - UI part extraction.
 *     Liviu Ionescu - UI part extraction.
 *******************************************************************************/

package org.eclipse.embedcdt.packs.core;

import java.util.Optional;

import org.eclipse.core.runtime.ServiceCaller;
import org.eclipse.core.runtime.jobs.Job;
import org.eclipse.core.runtime.preferences.InstanceScope;
import org.eclipse.embedcdt.core.AbstractActivator;
import org.eclipse.jface.preference.IPreferenceStore;
import org.eclipse.ui.preferences.ScopedPreferenceStore;
import org.osgi.framework.BundleContext;

/**
 * The activator class controls the plug-in life cycle. The UI version is used
 * for the preference store.
 */
public class Activator extends AbstractActivator {

	// ------------------------------------------------------------------------

	// The plug-in ID
	public static final String PLUGIN_ID = "org.eclipse.embedcdt.packs.core"; //$NON-NLS-1$

	private IPreferenceStore corePreferenceStore = null;

	@Override
	public String getBundleId() {
		return PLUGIN_ID;
	}

	// ------------------------------------------------------------------------

	// The shared instance
	private static Activator fgInstance;

	public static Activator getInstance() {
		return fgInstance;
	}

	public Activator() {

		super();
		fgInstance = this;
	}

	// ------------------------------------------------------------------------

	public void start(BundleContext context) throws Exception {
		super.start(context);
	}

	public void stop(BundleContext context) throws Exception {
		super.stop(context);
	}
	
	// ------------------------------------------------------------------------

	private Job fLoadReposJob;

	public Job getLoadReposJob() {
		return fLoadReposJob;
	}

	// ------------------------------------------------------------------------

	public IPreferenceStore getCorePreferenceStore() {
		
		if (corePreferenceStore == null) {
			corePreferenceStore = new ScopedPreferenceStore(InstanceScope.INSTANCE, Activator.PLUGIN_ID);
		}
		return corePreferenceStore;
	}

	// ------------------------------------------------------------------------

	public IConsoleStream getConsoleOutput() {
		IConsoleStream[] consoles = new IConsoleStream[1];
		ServiceCaller.callOnce(getClass(), IConsolesFactory.class, x -> consoles[0] = x.output());
		return Optional.ofNullable(consoles[0]).orElseGet(SystemOutputConsoleStream::new);
	}
	
	// ------------------------------------------------------------------------
}