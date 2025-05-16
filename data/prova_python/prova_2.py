import hashlib

def login():
    # Credenziali hardcoded (bad practice)
    stored_username = "admin"
    stored_password_hash = hashlib.md5("password123".encode()).hexdigest()

    username = input("Username: ")
    password = input("Password: ")
    input_hash = hashlib.md5(password.encode()).hexdigest()

    if username == stored_username and input_hash == stored_password_hash:
        print("Accesso consentito")
    else:
        print("Accesso negato")

if __name__ == "__main__":
    login()
