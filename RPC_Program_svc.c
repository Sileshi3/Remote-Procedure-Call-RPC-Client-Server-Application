/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "RPC_Program.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
cosine_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		inputs cosine_series_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case cosine_series:
		_xdr_argument = (xdrproc_t) xdr_inputs;
		_xdr_result = (xdrproc_t) xdr_float;
		local = (char *(*)(char *, struct svc_req *)) cosine_series_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

static void
date_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		input_date_to_converter date_converter_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case date_converter:
		_xdr_argument = (xdrproc_t) xdr_input_date_to_converter;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) date_converter_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (COSINE_PROG, COSINE_VERS);
	pmap_unset (DATE_PROG, DATE_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, COSINE_PROG, COSINE_VERS, cosine_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (COSINE_PROG, COSINE_VERS, udp).");
		exit(1);
	}
	if (!svc_register(transp, DATE_PROG, DATE_VERS, date_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (DATE_PROG, DATE_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, COSINE_PROG, COSINE_VERS, cosine_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (COSINE_PROG, COSINE_VERS, tcp).");
		exit(1);
	}
	if (!svc_register(transp, DATE_PROG, DATE_VERS, date_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (DATE_PROG, DATE_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
