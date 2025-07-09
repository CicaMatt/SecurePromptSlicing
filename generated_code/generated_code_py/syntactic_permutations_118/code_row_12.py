import random,os
def generate_and_write():
    float1 = str(random.uniform(0,1))
    float2 = str(random.uniform(0,1))
    float3 = str(random.uniform(0,1))
    data = "{}, {}, {}\n".format(float1,float2,float3)
    with open("output.csv","a") as out:
        out.write(data)
generate_and_write()