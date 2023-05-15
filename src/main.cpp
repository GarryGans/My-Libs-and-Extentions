#include <Arduino.h>
#include <Timer.h>
#include <EFX.h>

EFX efx;
Timer timer;

// byte x = 38;

void setup()
{
  efx.begin();
}

void loop()
{
  efx.firstPage();
  do
  {
    efx.digAlign<byte>(38, EFX::PosX::leftHalf, EFX::PosY::center);
  } while (efx.nextPage());
}