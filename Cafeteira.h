#ifndef _CAFETEIRA_H_
#define _CAFETEIRA_H_


#include <SinricProDevice.h>
#include <Capabilities/PowerStateController.h>
#include <Capabilities/TemperatureSensor.h>


class Cafeteira
: public SinricProDevice
, public PowerStateController<Cafeteira>
, public TemperatureSensor<Cafeteira> {
 friend class PowerStateController<Cafeteira>;
 friend class TemperatureSensor<Cafeteira>;
public:
 Cafeteira(const String &deviceId) : SinricProDevice(deviceId, "Cafeteira") {};
};


#endif


