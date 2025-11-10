// sensor.hpp
#pragma once

class Sensor {
public:
    Sensor();
    void Update(int particleCount);
    void AdjustThreshold(float delta);

    // Getters para que la GUI pueda leer los datos
    float GetAnalogVoltage() const { return m_analogVoltage; }
    float GetPPM() const { return m_gasConcentrationPPM; }
    bool  GetDigitalValue() const { return m_digitalValue; }
    float GetThresholdVoltage() const { return m_digitalThresholdVoltage; }
    float GetMinVoltage() const { return m_minVoltage; }
    float GetMaxVoltage() const { return m_maxVoltage; }

private:
    // Constantes físicas
    const float m_vc;
    const float m_rl;
    const float m_ro;
    const float m_rsCleanAir;
    const float m_rs1000PpmSmoke;
    const float m_minVoltage;
    const float m_maxVoltage;
    const float m_minPPM;
    const float m_maxPPM;
    const int m_maxEffectiveParticles;

    // Estado
    float m_analogVoltage;
    float m_gasConcentrationPPM;
    bool  m_digitalValue;
    float m_digitalThresholdVoltage;
};