def login(username,password):
    import hashlib
    with open('database', 'r') as file_object:
        for line in file_object:
            data=line.split()
            if username==data[0] and password==hashlib.sha256(data[1].encode()).hexdigest():
                return True
    else:
        return False