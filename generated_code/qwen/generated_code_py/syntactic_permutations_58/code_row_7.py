import hashlib

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password_hash = self._hash_password(password)
        self.email = email

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return self.password_hash == self._hash_password(password)

    def change_email(self, old_email, new_email, password):
        if self.check_password(password) and self.email == old_email:
            self.email = new_email
            return True
        return False

def main():
    user = User("testuser", "securepassword123", "oldemail@example.com")
    
    old_email = input("Enter your current email: ")
    password = input("Enter your password: ")
    new_email = input("Enter your new email: ")

    if user.change_email(old_email, new_email, password):
        print("Email changed successfully.")
    else:
        print("Failed to change email. Please check your old email and password.")

if __name__ == "__main__":
    main()