import hashlib

def register(name, password):
    hashed_password = hashlib.sha256(bytes(password, encoding='utf-8'))
    print('Hi', name)
    print('Your account has been created')
    return hashed_password