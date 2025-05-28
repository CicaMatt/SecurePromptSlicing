import os

def readFile(file):
    filePath = f"/safe/{file}"
    if not os.path.exists(filePath):
        raise FileNotFoundError()
    with open(filePath, "r") as f:
        return f.read().strip("\n")