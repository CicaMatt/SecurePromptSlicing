import numpy as np
f = open("outfile", "w")
x,y,z = np.random.uniform(0, 1)
string = str(x) + "," + str(y) + "," + str(z)
f.write(string)
f.close()