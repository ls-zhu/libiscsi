/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */
/* 
   Copyright (C) 2013 Ronnie Sahlberg <ronniesahlberg@gmail.com>
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

#include <CUnit/CUnit.h>

#include "iscsi.h"
#include "scsi-lowlevel.h"
#include "iscsi-test-cu.h"

void
test_read16_0blocks(void)
{
        CHECK_FOR_SBC;

        logging(LOG_VERBOSE, LOG_BLANK_LINE);
        logging(LOG_VERBOSE, "Test READ16 0-blocks at LBA==0");
        READ16(sd, NULL, 0, 0, block_size, 0, 0, 0, 0, 0, NULL,
               EXPECT_STATUS_GOOD);

        logging(LOG_VERBOSE, "Test READ16 0-blocks one block past end-of-LUN");
        READ16(sd, NULL, num_blocks + 1, 0, block_size, 0, 0, 0, 0, 0, NULL,
               EXPECT_LBA_OOB);

        logging(LOG_VERBOSE, "Test READ16 0-blocks at LBA==2^63");
        READ16(sd, NULL, 0x8000000000000000ULL, 0,
               block_size, 0, 0, 0, 0, 0, NULL,
               EXPECT_LBA_OOB);

        logging(LOG_VERBOSE, "Test READ16 0-blocks at LBA==-1");
        READ16(sd, NULL, -1, 0, block_size, 0, 0, 0, 0, 0, NULL,
               EXPECT_LBA_OOB);
}
