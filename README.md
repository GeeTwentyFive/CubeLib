https://github.com/GeeTwentyFive/CubeFileFormat


# Loader usage
```c
uint32_t num_cubes;
Cube_Cube* cubes = Cube_Load("PATH/TO/CUBES.cubes", &num_cubes);
if (!cubes) {
        puts("Failed to load EXAMPLE.cubes");
        return 1;
}

// use `cubes` & `num_cubes`...

free(cubes);
```


# Writer usage example
```c
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

if (!Cube_Write(cubes, NUM_CUBES, "EXAMPLE.cubes")) {
        puts("Failed to write cubes");
        return 1;
}
```