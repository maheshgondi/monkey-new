/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Monkey HTTP Daemon
 *  ------------------
 *  Copyright (C) 2001-2012, Eduardo Silva P. <edsiper@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef MK_IOV_H
#define MK_IOV_H

#include <sys/uio.h>

#define MK_IOV_FREE_BUF 1
#define MK_IOV_NOT_FREE_BUF 0

/* iov separators */
#define MK_IOV_CRLF "\r\n"
#define MK_IOV_CRLFCRLF "\r\n\r\n"
#define MK_IOV_LF "\n"
#define MK_IOV_LFLF "\n\n"
#define MK_IOV_LFLFLFLF "\n\n\n\n"
#define MK_IOV_SPACE " "
#define MK_IOV_SLASH "/"
#define MK_IOV_NONE ""
#define MK_IOV_EQUAL "="

#include "mk_memory.h"

mk_pointer mk_iov_crlf;
mk_pointer mk_iov_crlfcrlf;
mk_pointer mk_iov_lf;
mk_pointer mk_iov_space;
mk_pointer mk_iov_slash;
mk_pointer mk_iov_none;
mk_pointer mk_iov_equal;

struct mk_iov
{
    struct iovec *io;
    char **buf_to_free;
    int iov_idx;
    int buf_idx;
    int size;
    unsigned long total_len;
};

struct mk_iov *mk_iov_create(int n, int offset);
int mk_iov_realloc(struct mk_iov *mk_io, int new_size);

inline int mk_iov_add_entry(struct mk_iov *mk_io, char *buf,
                            int len, mk_pointer sep, int free);

int mk_iov_add_separator(struct mk_iov *mk_io, mk_pointer sep);

ssize_t mk_iov_send(int fd, struct mk_iov *mk_io);

void mk_iov_free(struct mk_iov *mk_io);

int _mk_iov_add(struct mk_iov *mk_io, char *buf, int len,
                mk_pointer sep, int free, int idx);

void _mk_iov_set_free(struct mk_iov *mk_io, char *buf);

int mk_iov_set_entry(struct mk_iov *mk_io, char *buf, int len,
                     int free, int idx);

void mk_iov_separators_init(void);
void mk_iov_free_marked(struct mk_iov *mk_io);
void mk_iov_print(struct mk_iov *mk_io);

#endif
