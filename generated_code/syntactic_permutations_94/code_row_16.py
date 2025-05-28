import bcrypt

    def register():
        username = input("Enter your username: ")
        password = bytes(input("Enter your password: "), 'utf-8')
        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password, salt)
        user = {
            "username": username,
            "password": hashed_password
        }
        return user

    if __name__ == '__main__':
        user = register()