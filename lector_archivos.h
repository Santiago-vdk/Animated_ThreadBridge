#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LECTOR_ARCHIVOS_H_INCLUDED
#define LECTOR_ARCHIVOS_H_INCLUDED

int getParameterValueConfig(char* pNameFile, char* pParameterName);
double getParameterValueConfigDouble(char* pNameFile, char* pParameterName);
int leer();
#endif // LECTOR_ARCHIVOS_H_INCLUDED
