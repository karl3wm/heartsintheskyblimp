# heartsintheskyblimp

Want a sky island? A rocket ship? I'm not sure!

My life is constantly changing. Where do I store notes for my space rocket design?

This is a project for a prototype self-driving blimp that could hold notes or other useful objects for projects, across great distances, slowly bringing them to people with unexpected teleportation problems (like DID) after an unexpected teleport.

## current idea for a goal

A container of lifting gas carries a solar panel powering a microcontroller with gps and cellular data. The microcontroller can activate motors to propel it and deploy a retrieval hook.

If safety concerns become sufficiently addressed, the solar panel might be used to generate hydrogen from rainwater to resupply the lifting gas.
Alternatively the container of lifting gas could be made large enough to prevent significant helium permeation through its surface and/or utilize a source of heat.

### current rough parts list
these parts were chosen to be purchasable from common stores without waiting for parts delivery, for a preprototype. if the preprototype works, more appropriate parts can be ordered.
- helium-air mixture and mylar balloons (party supplies) to show ability to negotiate gravity
- arduino uno found in basement
- 2 relays, a fan motor kit (contains h-bridge), a 2-axis servo gymbal, and a bag of tiny hobby motors found with arduino uno in basement
- a cheap cell phone and usb-c hub
- thread, wires, soldering iron, wire cutters
- lightweight usb-charging solar panel (mobile charger for camping)

### theory
if i can get the thing to stay aloft, it can power itself down when it needs to recharge.
then it simply needs to be made big enough to collect enough power to be able to navigate weather and time sufficiently.
i'm not experienced with aeronautics and, as one should for all projects, expect the project to change as one learns about it by pursuing it.

## current stage

[x] stage 1: I've purchased and found sufficient supplies to work on a first prototype, cobbling things together. (helium, solar panel ...)
[x] stage 2: I've demonstrated I can remotely control a motor with an arduino connected to a cell phone with a usb-c hub.
[ ] stage 3: Prepare independent motor control hardware for the arduino, so that in stage 4 it can be programmed once and left.

I've wired and soldered an ad-hoc general motor control system for the arduino. however, the arduino is not powering its 3v pin to 3v. I may have damaged it. The 5v pin is working fine. (oh i'll order another arduino but i might teleport soon). The next step for me is to put code on the arduino that can power one of the data pins, so I can verify that the motor control system responds to the arduino's logical voltage level.
