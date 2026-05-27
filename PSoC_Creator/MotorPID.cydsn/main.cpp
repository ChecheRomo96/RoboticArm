/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

extern "C" {
    #include "project.h"
}

#include "Hardware.hpp"

#include <Foundation/Math.h>
#include <Foundation/Math/Matrix.h>
#include <Foundation/Math/Matrix/Matrix.h>

#include <stdio.h>

using namespace Foundation;

static void PrintFixedMatrix2x2(
    const Math::FixedMatrix<float, 2, 2>& m
) {

    char buffer[128];

    sprintf(
        buffer,
        "[ %.2f %.2f ]\r\n"
        "[ %.2f %.2f ]\r\n",
        m[0][0],
        m[0][1],
        m[1][0],
        m[1][1]
    );

    UART_PutString(buffer);
}

static void PrintDynamicMatrix(
    const Math::DynamicMatrix<float>& m
) {

    char buffer[64];

    for(uint32_t i = 0; i < m.RowsCount(); i++) {

        for(uint32_t j = 0; j < m.ColsCount(); j++) {

            sprintf(
                buffer,
                "%.2f ",
                m[i][j]
            );

            UART_PutString(buffer);
        }

        UART_PutString("\r\n");
    }
}

int main(void)
{
    CyGlobalIntEnable;

    UART_Start();
    Hardware::Start();

    UART_PutString("\r\n=== FIXED MATRIX TEST ===\r\n");

    Math::FixedMatrix<float, 2, 2> A;
    Math::FixedMatrix<float, 2, 2> B;
    Math::FixedMatrix<float, 2, 2> C;

    A[0][0] = 1.0f;
    A[0][1] = 2.0f;
    A[1][0] = 3.0f;
    A[1][1] = 4.0f;

    B[0][0] = 5.0f;
    B[0][1] = 6.0f;
    B[1][0] = 7.0f;
    B[1][1] = 8.0f;

    Math::Multiply(A, B, C);

    UART_PutString("A * B:\r\n");
    PrintFixedMatrix2x2(C);

    C *= 0.5f;

    UART_PutString("\r\nScaled by 0.5:\r\n");
    PrintFixedMatrix2x2(C);

    UART_PutString("\r\n=== DYNAMIC MATRIX TEST ===\r\n");

    Math::DynamicMatrix<float> D(2, 2);
    Math::DynamicMatrix<float> E(2, 2);
    Math::DynamicMatrix<float> F(2, 2);

    D[0][0] = 1.0f;
    D[0][1] = 2.0f;
    D[1][0] = 3.0f;
    D[1][1] = 4.0f;

    E[0][0] = 2.0f;
    E[0][1] = 0.0f;
    E[1][0] = 1.0f;
    E[1][1] = 2.0f;

    if(Math::Multiply(D, E, F)) {

        UART_PutString("D * E:\r\n");
        PrintDynamicMatrix(F);
    }
    else {

        UART_PutString("Dynamic multiply failed\r\n");
    }

    F *= 2.0f;

    UART_PutString("\r\nScaled by 2.0:\r\n");
    PrintDynamicMatrix(F);

    for(;;) {

    }
}

/* [] END OF FILE */