from vect3 import*

class Rayon:
    def __init__(self, ori : Vect3, dir : Vect3):
        self.ori = ori
        self.dir = dir
    
def point_du_rayon(t, rayon: Rayon):
    return rayon.ori + rayon.dir*t
