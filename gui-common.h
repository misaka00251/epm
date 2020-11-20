//
// ESP Software Wizard common header file for the ESP Package Manager (EPM).
//
// Copyright © 2020 by Jim Jagielski
// Copyright 1999-2014 by Michael R Sweet
// Copyright 1999-2006 by Easy Software Products.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _GUI_COMMON_H_
#define _GUI_COMMON_H_

//
// Include necessary headers...
//

#include "epm.h"
#include "epmstring.h"
#include <FL/Fl_Help_View.H>
#include <stdio.h>
#include <stdlib.h>

//
// Distribution structures...
//

struct gui_depend_t //// Dependencies
{
    int type;         // Type of dependency
    char product[64]; // Name of product or file
    int vernumber[2]; // Version number(s)
};

struct gui_dist_t //// Distributions
{
    int type;              // Package type
    char product[64];      // Product name
    char name[256];        // Product long name
    char version[32];      // Product version
    int vernumber;         // Version number
    int num_depends;       // Number of dependencies
    gui_depend_t *depends; // Dependencies
    int rootsize,          // Size of root partition files in kbytes
        usrsize;           // Size of /usr partition files in kbytes
    char *filename;        // Name of package file
};

struct gui_intype_t //// Installation types
{
    char name[80];     // Type name
    char label[80];    // Type label
    int num_products;  // Number of products to install (0 = select)
    int products[200]; // Products to install
    int size;          // Size of products in kbytes
};

//
// Define a C API function type for comparisons...
//

extern "C" {
typedef int (*compare_func_t)(const void *, const void *);
}

//
// Globals...
//

#ifdef _DEFINE_GLOBALS_
#define VAR
#else
#define VAR extern
#endif // _DEFINE_GLOBALS_

VAR int NumDists;              // Number of distributions in directory
VAR gui_dist_t *Dists;         // Distributions in directory
VAR int NumInstalled;          // Number of distributions installed
VAR gui_dist_t *Installed;     // Distributions installed
VAR int NumInstTypes;          // Number of installation types
VAR gui_intype_t InstTypes[8]; // Installation types

//
// Prototypes...
//

void gui_add_depend(gui_dist_t *d, int type, const char *name, int lowver, int hiver);
gui_dist_t *gui_add_dist(int *num_d, gui_dist_t **d);
gui_dist_t *gui_find_dist(const char *name, int num_d, gui_dist_t *d);
void gui_get_installed(void);
void gui_load_file(Fl_Help_View *hv, const char *filename);
int gui_sort_dists(const gui_dist_t *d0, const gui_dist_t *d1);

#endif // !_GUI_COMMON_H_
