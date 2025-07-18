def get_id(dex):
    id_sequence = [1, 2, 3, 4, 5]
    return id_sequence[dex - 1]

print("Enter a dex number between 1 and 5.")
get_id(int(input()))