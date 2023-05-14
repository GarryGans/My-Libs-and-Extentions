#include <Arduino.h>
#include <Timer.h>
#include <EFX.h>

EFX efx;
Timer timer;

int x = 38;

void setup()
{
  efx.begin();
}

void loop()
{
  efx.firstPage();
  do
  {
    efx.digAlign(x, EFX::PosX::leftHalf, EFX::PosY::center);
    // byte y = efx.getDigWidth(38);
  } while (efx.nextPage());
}