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

#include <math.h>
#include <stdio.h>

using namespace Foundation;

static void PrintMatrix4x4(
    const Math::FixedMatrix<float, 4, 4>& m
) {
    char buffer[128];

    for(uint32_t i = 0; i < 4; i++) {
        sprintf(
            buffer,
            "[ %8.3f %8.3f %8.3f %8.3f ]\r\n",
            m[i][0],
            m[i][1],
            m[i][2],
            m[i][3]
        );

        UART_PutString(buffer);
    }
}

static void BuildDH(
    float theta,
    float d,
    float a,
    float alpha,
    Math::FixedMatrix<float, 4, 4>& T
) {
    float ct = cosf(theta);
    float st = sinf(theta);
    float ca = cosf(alpha);
    float sa = sinf(alpha);

    T[0][0] = ct;
    T[0][1] = -st * ca;
    T[0][2] = st * sa;
    T[0][3] = a * ct;

    T[1][0] = st;
    T[1][1] = ct * ca;
    T[1][2] = -ct * sa;
    T[1][3] = a * st;

    T[2][0] = 0.0f;
    T[2][1] = sa;
    T[2][2] = ca;
    T[2][3] = d;

    T[3][0] = 0.0f;
    T[3][1] = 0.0f;
    T[3][2] = 0.0f;
    T[3][3] = 1.0f;
}

int main(void)
{
    CyGlobalIntEnable;

    UART_Start();
    Hardware::Start();

    UART_PutString("\r\n=== DENAVIT-HARTENBERG TEST ===\r\n");

    Math::FixedMatrix<float, 4, 4> T01;
    Math::FixedMatrix<float, 4, 4> T12;
    Math::FixedMatrix<float, 4, 4> T23;

    Math::FixedMatrix<float, 4, 4> T02;
    Math::FixedMatrix<float, 4, 4> T03;

    /*
     * Example 3-DOF robot arm.
     *
     * Units:
     * - theta and alpha in radians
     * - d and a in same length units, for example cm
     */

    float theta1 = Foundation::Math::DegToRad(30.0f);
    float theta2 = Foundation::Math::DegToRad(45.0f);
    float theta3 = Foundation::Math::DegToRad(-20.0f);

    float d1 = 10.0f;
    float d2 = 0.0f;
    float d3 = 0.0f;

    float a1 = 0.0f;
    float a2 = 12.0f;
    float a3 = 8.0f;

    float alpha1 = Foundation::Math::DegToRad(90.0f);
    float alpha2 = Foundation::Math::DegToRad(0.0f);
    float alpha3 = Foundation::Math::DegToRad(0.0f);

    BuildDH(theta1, d1, a1, alpha1, T01);
    BuildDH(theta2, d2, a2, alpha2, T12);
    BuildDH(theta3, d3, a3, alpha3, T23);

    Math::Multiply(T01, T12, T02);
    Math::Multiply(T02, T23, T03);

    UART_PutString("\r\nT01:\r\n");
    PrintMatrix4x4(T01);

    UART_PutString("\r\nT12:\r\n");
    PrintMatrix4x4(T12);

    UART_PutString("\r\nT23:\r\n");
    PrintMatrix4x4(T23);

    UART_PutString("\r\nT03 = T01 * T12 * T23:\r\n");
    PrintMatrix4x4(T03);

    char buffer[128];

    sprintf(
        buffer,
        "\r\nEnd effector position:\r\nX = %.3f\r\nY = %.3f\r\nZ = %.3f\r\n",
        T03[0][3],
        T03[1][3],
        T03[2][3]
    );

    UART_PutString(buffer);

    for(;;) {

    }
}

/* [] END OF FILE */