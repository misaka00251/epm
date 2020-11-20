/*
 * Support functions for the ESP Package Manager (EPM).
 *
 * Copyright © 2020 by Jim Jagielski
 * Copyright 1999-2014 by Michael R Sweet
 * Copyright 1999-2006 by Easy Software Products.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Include necessary headers...
 */

#include "epm.h"

/*
 * 'get_vernumber()' - Convert a version string to a number...
 */

int                                /* O - Version number */
get_vernumber(const char *version) /* I - Version string */
{
    int numbers[4],  /* Raw version numbers */
        nnumbers,    /* Number of numbers in version */
        temp,        /* Temporary version number */
        offset;      /* Offset for last version number */
    const char *ptr; /* Pointer into string */

    /*
     * Loop through the version number string and construct a version number.
     */

    memset(numbers, 0, sizeof(numbers));

    for (ptr = version; *ptr && !isdigit(*ptr & 255); ptr++)
        ;
    /* Skip leading letters, periods, etc. */

    for (offset = 0, temp = 0, nnumbers = 0; *ptr && !isspace(*ptr & 255); ptr++)
        if (isdigit(*ptr & 255))
            temp = temp * 10 + *ptr - '0';
        else {
            /*
             * Add each mini version number (m.n.p) and patch/pre stuff...
             */

            if (nnumbers < 4) {
                numbers[nnumbers] = temp;
                nnumbers++;
            }

            temp = 0;

            if (*ptr == '.')
                offset = 0;
            else if (*ptr == 'p' || *ptr == '-') {
                if (strncmp(ptr, "pre", 3) == 0) {
                    ptr += 2;
                    offset = -20;
                } else
                    offset = 0;

                nnumbers = 3;
            } else if (*ptr == 'b') {
                offset = -50;
                nnumbers = 3;
            } else { /* if (*ptr == 'a') */
                offset = -100;
                nnumbers = 3;
            }
        }

    if (nnumbers < 4)
        numbers[nnumbers] = temp;

    /*
     * Compute the version number as MMmmPPpp + offset
     */

    return (((numbers[0] * 100 + numbers[1]) * 100 + numbers[2]) * 100 + numbers[3] +
            offset);
}
