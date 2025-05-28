def check_mod(username, password):
        return True if username == "admin" and password == "password1234" else False

    if __name__ == "__main__":
        print(check_mod("admin", "password"))