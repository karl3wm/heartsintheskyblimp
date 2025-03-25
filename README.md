# heartsintheskyblimp

Want a sky island? A rocket ship? I'm not sure!

My life is constantly changing. Where do I store notes for my space rocket design?

This is a project for a prototype self-driving blimp that could hold notes or other useful objects for projects, across great distances, slowly bringing them to people with unexpected teleportation problems (like DID) after an unexpected teleport.

## current idea for a goal

A container of lifting gas carries a solar panel powering a microcontroller with gps and cellular data. The microcontroller can activate motors to propel it and deploy a retrieval hook.

If safety concerns become sufficiently addressed, the solar panel might be used to generate hydrogen from rainwater to resupply the lifting gas.
Alternatively the container of lifting gas could be made large enough to prevent significant helium permeation through its surface and/or utilize a source of heat.

### current rough parts list

I started with these parts to be findable near me or purchasable from common stores without waiting for parts delivery, for a preprototype.

If the preprototype works, cheaper and more appropriate parts can be ordered.

- helium-air mixture and mylar balloons (party supplies) to show ability to negotiate gravity
- arduino uno found in basement
- 2 relays, a fan motor kit (contains h-bridge), a 2-axis servo gymbal, and a bag of tiny hobby motors found with arduino uno in basement
- a cheap cell phone and usb-c hub
- thread, wires, soldering iron, wire cutters
- lightweight usb-charging solar panel (mobile charger for camping)

### theory

If i can get the thing to stay aloft, it can power itself down when it needs to recharge.

Then it simply needs to be made big enough to collect enough power to be able to navigate weather and time sufficiently.

As one should for all projects, I expect the project to change as one learns about it by pursuing it.

## current stage

- [x] stage 1: I've purchased and found sufficient supplies to work on a first prototype, cobbling things together. (helium, solar panel ...)
- [x] stage 2: I've demonstrated I can remotely control a motor with an arduino connected to a cell phone with a usb-c hub.
- [ ] stage 3: I've wired the relays, fan control board, and servos all together into 6 data pins on the arduino with supply and ground distribution, and shown the wiring works to control up to 4 motors and 2 servos. However, I need to update the wiring to separate the motor power from the arduino's USB link better.
- [ ] stage 4: I've made a basic arduino serial server for pigpiod allowing use of the pins and servos with an existing tool. I had to jerryrig a change to the power wiring a little to stop the motors from immediately resetting the USB connection, and now need to revisit stage 3 just a little bit to figure out how to secure the new wiring, and then I can bundle the parts together and would be on to stage 5.
