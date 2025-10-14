from rayon import *
from vect3 import *
import os


#paramètre de l'image
im = open(f"{os.getcwd()}/restultat.ppm", "w")
image_ratio = 1 
image_width = 256
image_height = image_width * image_ratio

#caméra
distance_focale = 5
centre_camera = Vect3(0, 0, 0)
ecran_width = 10
ecran_height = ecran_width * image_ratio

#base de l'écran
u = Vect3(ecran_width, 0, 0)
v = Vect3(0, -ecran_height, 0)
delta_u = u/image_width
delta_v = v/image_height

#origine de l'écran
coin_superieur_gauche = centre_camera - Vect3(ecran_width/2, ecran_height, distance_focale)
coordonnees_pixel_0 = coin_superieur_gauche + delta_u/2 + delta_v/2


def colore_rayon_degrade(rayon):
    r = rayon.dir.x / (image_width-1)
    g = rayon.dir.y / (image_height-1)
    b = 0.0
    return r, g, b 



for i in range(0, image_width - 1):
    for j in range(0, image_height-1):
        coordonnees_pixel = coordonnees_pixel_0 + delta_u*float(i) + delta_v*float(j)
        direction = coordonnees_pixel - centre_camera
        rayon = Rayon(centre_camera, direction)

        ir, ig, ib = colore_rayon_degrade(rayon)




        im.write(f"{ir} {ig} {ib}\n")

im.close()

