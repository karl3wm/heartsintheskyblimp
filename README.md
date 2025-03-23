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
- [ ] stage 3: Prepare independent motor control hardware for the arduino, so that in an upcoming stage it can be programmed once and left.

I've wired and soldered an ad-hoc general motor control system for the arduino. I failed to detect 3V on the 3V pin with the tools I had, but I've now verified that the hobby fan control board (h-bridge) will function with the logic levels of the Arduino and successfully toggled power to a motor through my control hardware. I still need to verify the relays will accept the board logic levels (I don't know them at this time), decide on a stable wiring to the pins, and bundle it together with the phone.

I'll be connecting 2 pins for servos, 2 pins for the h-bridge, and 2 pins for the 2 relays, allowing control of a maximum of 2 servos and 4 motors.
