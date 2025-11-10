// sensor.cpp
#include "sensor.hpp"
#include <cmath>
#include <algorithm>

// Función de mapeo (privada a este archivo)
namespace {
    float map(float value, float start1, float stop1, float start2, float stop2) {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    }
}

Sensor::Sensor() :
    m_vc(5000.0f),
    m_rl(20000.0f),
    m_ro(6800.0f),
    m_rsCleanAir(10.0f * m_ro),
    m_rs1000PpmSmoke(2.0f * m_ro),
    m_minVoltage(m_vc* (m_rl / (m_rsCleanAir + m_rl))),
    m_maxVoltage(m_vc* (m_rl / (m_rs1000PpmSmoke + m_rl))),
    m_minPPM(10.0f),
    m_maxPPM(1000.0f),
    m_maxEffectiveParticles(300),
    m_analogVoltage(m_minVoltage),
    m_gasConcentrationPPM(m_minPPM),
    m_digitalValue(false),
    m_digitalThresholdVoltage((m_minVoltage + m_maxVoltage) / 2.0f)
{
}

void Sensor::Update(int particleCount) {
    // 1. Calcular concentración
    float normalizedConcentration = std::min(1.0f, static_cast<float>(particleCount) / m_maxEffectiveParticles);
    float sensorResponse = std::pow(normalizedConcentration, 0.7f);

    // 2. Mapear PPM (para visualización)
    m_gasConcentrationPPM = map(normalizedConcentration, 0.0f, 1.0f, m_minPPM, m_maxPPM);

    // 3. Calcular Resistencia (Rs)
    float currentRs = map(sensorResponse, 0.0f, 1.0f, m_rsCleanAir, m_rs1000PpmSmoke);

    // 4. Calcular Voltaje (Vout)
    m_analogVoltage = m_vc * (m_rl / (currentRs + m_rl));

    // 5. Calcular Estado Digital
    m_digitalValue = (m_analogVoltage > m_digitalThresholdVoltage);
}

void Sensor::AdjustThreshold(float delta) {
    m_digitalThresholdVoltage += delta * 50.0f; // Ajuste en pasos de 50mV
    m_digitalThresholdVoltage = std::max(m_minVoltage, std::min(m_maxVoltage, m_digitalThresholdVoltage));
}