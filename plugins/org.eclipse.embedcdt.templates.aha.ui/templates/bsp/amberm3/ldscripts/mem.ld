/******************************************************************************
* @file     mem.ld
* @brief    Memory Spaces Definitions
******************************************************************************/
/*
* Copyright (c) 2009-2020 Arm Limited. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*
*-------- <<< Use Configuration Wizard in Context Menu >>> -------------------
*/

/*---------------------- Flash Configuration ----------------------------------
 <h> Flash Configuration
   <o0> Flash Base Address <0x0-0xFFFFFFFF:8>
   <o1> Flash Size (in Bytes) <0x0-0xFFFFFFFF:8>
 </h>
 -----------------------------------------------------------------------------*/
__ROM_BASE = 0x00000000;
__ROM_SIZE = $(AMBERM3flashSize)K;

/*--------------------- Embedded RAM Configuration ----------------------------
 <h> RAM Configuration
   <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
   <o1> RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
 </h>
-----------------------------------------------------------------------------*/
__RAM_BASE = 0x20000000;
__RAM_SIZE = $(AMBERM3ramSize)K;

/*
*-------------------- <<< end of configuration section >>> -------------------
*/

MEMORY
{
 FLASH (rx)  : ORIGIN = __ROM_BASE, LENGTH = __ROM_SIZE
 RAM   (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}
