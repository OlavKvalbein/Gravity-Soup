# Gravity-Soup
Generates images by computing positions of particles in a gravity field. Each pixel corresponds to one particle. After a set time the pixel will be colored according to the gravity well that its particle ends up closest to. Currently all particles have the same mass and inital velocity, and the gravity wells are equally strong. The project is written from scratch using only libc.

![anim1](https://github.com/OlavKvalbein/Gravity-Soup/assets/149806181/be533ce4-f359-48d4-9a10-5cd13453f8e9)

To calculate the positions the rk4 method is used, in addition the acceleration is clamped to avoid innaccuracy by the wells and grainyness. Bellow is the same simulation clamped at different accelerations:
![clamp10](https://github.com/OlavKvalbein/Gravity-Soup/assets/149806181/b954f839-2220-409d-9c5c-8779e04abeae)
![clamp50](https://github.com/OlavKvalbein/Gravity-Soup/assets/149806181/92a12879-8dcf-4e68-915b-9f5d7f6d6e34)
![clamp100](https://github.com/OlavKvalbein/Gravity-Soup/assets/149806181/0aca366c-0ea5-4dc4-bc9d-cc9d0555ba08)

Heres one that has forces ~1/r instead of ~1/r^2:
![other](https://github.com/OlavKvalbein/Gravity-Soup/assets/149806181/7faeca34-8fdb-4b4f-bc40-e2a95776d800)
