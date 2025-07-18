import numpy as np
rand_floats = [str(x) for x in np.random.uniform(0, 1, size=3)]
output_string = ''.join(rand_floats)
with open('outputfile.txt', 'w') as f:
    f.write(output_string)