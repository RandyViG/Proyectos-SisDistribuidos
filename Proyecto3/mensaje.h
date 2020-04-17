#ifndef __MENSAJE_H__
#define __MENSAJE_H__

#define TAM_MAX_DATA 2

struct mensaje{
    int requestId;
    int arguments[TAM_MAX_DATA];
    int messageType;
    int operationId;
};

#endif
