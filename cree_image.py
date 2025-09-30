import os


im = open(f"{os.getcwd()}/restultat.ppm", "w")

image_height = 256
image_width = 256
im.write(f"P3\n {image_width} {image_height}\n255\n")

for x in range(image_height):
    for y in range(image_width):
        r = x / (image_width-1)
        g = y / (image_height-1)
        b = 0.0

        ir = int(255.999 * r)
        ig = int(255.999 * g)
        ib = int(255.999 * b)

        im.write(f"{ir} {ig} {ib}\n")

im.close()