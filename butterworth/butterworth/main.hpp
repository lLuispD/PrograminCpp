#pragma once


constexpr auto PI = 3.14159265358979323846;   // pi;
float RHA = 0;
float RHB = 0;
float RH1 = 0;
float RH2 = 0;
float CH1 = 0;
float CH2 = 0;
float k;
float QualityFactor = 10;
float CutFrequency = 1;			 // CutFrequency = 1 / (2 * PI * sqrt(RH1 * CH1 * RH2 * CH2));
float tmp_producto = 0; // Variable temporal para almacenar  RH1 * CH1 * RH2 * CH2
float tmp_subproducto = 0; // Almacena los sub productos luego de empezar a dar valores