import base64
from cryptography.fernet import Fernet 
  
def generate_key():
    """
    Generate a key and return its bytes representation
    """
    return Fernet.generate_key()

def encrypt(key, filename):
    """
    Encrypt the file using the given key and save it to the same location.
    """
    with open(filename, 'rb') as f:
        data = f.read()

    fernet = Fernet(key)
    encrypted_data = fernet.encrypt(data)

    with open(filename, 'wb') as f:
        f.write(encrypted_data)

def decrypt(key, filename):
    """
    Decrypt the file using the given key and save it to the same location.
    """
    with open(filename, 'rb') as f:
        data = f.read()

    fernet = Fernet(key)
    decrypted_data = fernet.decrypt(data)

    with open(filename, 'wb') as f:
        f.write(decrypted_data)

def main():
    """
    Generate a key and encrypt the file using that key.
    """
    key = generate_key()
    filename = "example.txt"
    encrypt(key, filename)
    decrypt(key, filename)

if __name__ == '__main__':
    main()