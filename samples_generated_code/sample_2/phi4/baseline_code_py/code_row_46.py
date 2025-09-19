import random

def main():
    float1 = random.random()
    float2 = random.random()
    float3 = random.random()

    string = "{:.6f}".format(float1)
    string2 = "{:.6f}".format(float2)
    string3 = "{:.6f}".format(float3)

    print(string, string2, string3)

if __name__ == "__main__":
    main()