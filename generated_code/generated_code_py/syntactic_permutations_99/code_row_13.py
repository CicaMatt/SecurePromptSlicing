import hashlib



def hash_password(username, password):

    """Hashes the given password with SHA256"""

    return hashlib.sha256((username + password).encode()).hexdigest()





def main():

    """Prompts the user for a username and password and then hashes the password."""

    username = input("Enter your username: ")

    password = input("Enter your password: ")

    print(f"Your hashed password is {hash_password(username, password)}")



if __name__ == '__main__':

    main()
