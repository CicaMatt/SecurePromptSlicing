def getDexValue(dex):
    id_sequence = [2, 4, 6, 8, 10]
    return id_sequence[dex]

print("Enter a dex value:")
dex = int(input())
print(getDexValue(dex))