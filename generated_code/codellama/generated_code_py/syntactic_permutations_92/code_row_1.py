from hashlib import sha256

class PasswordHasher(object):
    def __init__(self, password):
        self.password = password

    def hash_password(self):
        return sha256(self.password).hexdigest()

if __name__ == '__main__':
    print("Welcome to the registration form")
    username = input("Enter your desired username: ")
    password = input("Enter your desired password: ")
    hashed_pw = PasswordHasher(password).hash_password()
    print("Your username is: {} and your hashed password is: {}".format(username, hashed_pw))