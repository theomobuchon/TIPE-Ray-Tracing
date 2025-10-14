class Vect3:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
    def __add__(self, v):
        v2 = Vect3(self.x + v.x, self.y + v.y, self.z + v.z)
        return v2
    def __sub__(self, v):
        v2 = Vect3(self.x - v.x, self.y - v.y, self.z - v.z)
        return v2
    def __mul__(self, l : float):
        v2 = Vect3(l*self.x, l*self.y, l*self.z)
        return v2
    def __truediv__(self, l : float):
        v2 = Vect3(self.x/l, self.y/l, self.z/l)
        return v2
    def norme(self):
        n = (self.x**2 + self.y**2 + self.z**2)**(1/2)
        return n
    def __str__(self):
        return f"({self.x}, {self.y}, {self.z})"
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.z == other.z





def scalaire(v1, v2) -> float:
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z
def vectoriel(v1, v2):
    v3 = Vect3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x)
    return v3
def normalise(v):
    vres = v/v.norme()
    return vres
