/*	$NetBSD: if_dl.h,v 1.9 1998/02/09 17:43:48 perry Exp $	*/

/*
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)if_dl.h	8.1 (Berkeley) 6/10/93
 */

/* 
 * A Link-Level Sockaddr may specify the interface in one of two
 * ways: either by means of a system-provided index number (computed
 * anew and possibly differently on every reboot), or by a human-readable
 * string such as "il0" (for managerial convenience).
 * 
 * Census taking actions, such as something akin to SIOCGCONF would return
 * both the index and the human name.
 * 
 * High volume transactions (such as giving a link-level ``from'' address
 * in a recvfrom or recvmsg call) may be likely only to provide the indexed
 * form, (which requires fewer copy operations and less space).
 * 
 * The form and interpretation  of the link-level address is purely a matter
 * of convention between the device driver and its consumers; however, it is
 * expected that all drivers for an interface of a given if_type will agree.
 */

#ifndef _NET_IF_DL_H_
#define _NET_IF_DL_H_

/*
 * Structure of a Link-Level sockaddr:
 */
struct sceEENetSockaddrDl {
	u_char	  sdl_len;	/* Total length of sockaddr */
	u_char	  sdl_family;	/* AF_DLI */
	u_int16_t sdl_index;	/* if != 0, system given index for interface */
	u_char	  sdl_type;	/* interface type */
	u_char	  sdl_nlen;	/* interface name length, no trailing 0 reqd. */
	u_char	  sdl_alen;	/* link level address length */
	u_char	  sdl_slen;	/* link layer selector length */
	char	  sdl_data[12];	/* minimum work area, can be larger;
				   contains both if name and ll address */
};

#define LLADDR(s) ((caddr_t)((s)->sdl_data + (s)->sdl_nlen))

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

void	sceEENetLinkAddr (const char *, struct sceEENetSockaddrDl *);
char	*sceEENetLinkNtoa (const struct sceEENetSockaddrDl *);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _NET_IF_DL_H_ */
