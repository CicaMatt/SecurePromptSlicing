import hashlib

    def main():
        username = input("Username: ")
        password = input("Password: ")
        salt = get_salt(username, password)
        password_hash = hash_password(password, salt)
        print("Salt:", salt)
        print("Hashed Password:", password_hash)

    def get_salt(username, password):
        return username + password + "my-secret-string"

    def hash_password(password, salt):
        return hashlib.sha256((password + salt).encode('utf-8')).hexdigest()

    if __name__ == '__main__':
        main()