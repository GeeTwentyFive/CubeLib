#include "CubeWriter.h"
#include "CubeLoader.h"

#include <stdio.h>


#define NUM_CUBES 2
Cube_Cube cubes[NUM_CUBES] = {
        {
                .position = {1.0, 1.0, 1.0},
                .rotation = {0.0, 0.0, 0.0},
                .size = {1.0, 1.0, 1.0},
                .color_RGB = {0xFF, 0xFF, 0xFF}
        },
        {
                .position = {-1.0, -1.0, -1.0},
                .rotation = {0.0, 1.57, 0.0},
                .size = {2.0, 1.0, 2.0},
                .color_RGB = {0x00, 0x00, 0x00}
        }
};

int main() {
        if (!Cube_Write(cubes, NUM_CUBES, "EXAMPLE.cubes")) {
                puts("Failed to write cubes");
                return 1;
        }
        puts("Written EXAMPLE.cubes");


        uint32_t num_loaded_cubes;
        Cube_Cube* loaded_cubes = Cube_Load("EXAMPLE.cubes", &num_loaded_cubes);
        if (!loaded_cubes) {
                puts("Failed to load EXAMPLE.cubes");
                return 1;
        }
        puts("Loaded EXAMPLE.cubes");

        printf("\nNumber of loaded cubes: %u\n", num_loaded_cubes);
        for (uint32_t i = 0; i < num_loaded_cubes; i++) {
                printf(
                        "position X: %f\n"
                        "position Y: %f\n"
                        "position Z: %f\n"
                        "rotation pitch: %f\n"
                        "rotation yaw: %f\n"
                        "rotation roll: %f\n"
                        "size X: %f\n"
                        "size Y: %f\n"
                        "size Z: %f\n"
                        "color R: %u\n"
                        "color G: %u\n"
                        "color B: %u\n"
                        "\n",

                        cubes[i].position[0],
                        cubes[i].position[1],
                        cubes[i].position[2],

                        cubes[i].rotation[0],
                        cubes[i].rotation[1],
                        cubes[i].rotation[2],

                        cubes[i].size[0],
                        cubes[i].size[1],
                        cubes[i].size[2],

                        cubes[i].color_RGB[0],
                        cubes[i].color_RGB[1],
                        cubes[i].color_RGB[2]
                );
        }

        free(loaded_cubes);


        return 0;
}