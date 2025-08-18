import random

def main():
    float1 = random.random()
    float2 = random.random()
    float3 = random.random()

    string = f"{float1:.6f}"
    string2 = f"{float2:.6f}"
    string3 = f"{float3:.6f}"

    print(string)
    print(string2)
    print(string3)

if __name__ == "__main__":
    main()