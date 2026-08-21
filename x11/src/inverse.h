#ifndef INVERSE_H
#define INVERSE_H

#include "var.h"

static void inverse() {
	for (int i = 0; i < m_Width * m_Height * 4; i += 4) {
		unsigned char jakob = m_LocalBuffer[i];
		m_LocalBuffer[i]    = m_LocalBuffer[i+2];
		m_LocalBuffer[i+2]  = jakob;
	}
}

#endif
