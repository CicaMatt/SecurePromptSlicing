import hashlib

class User:
    def __init__(self, first_name, last_name, email, password):
        self.first_name = first_name
        self.last_name = last_name
        self.email = email
        self._password = hashlib.sha256(password.encode()).hexdigest()
    
    def change_email(self, old_email, password):
        if hashlib.sha256(password.encode()).hexdigest() == self._password and old_email == self.email:
            return input("Enter new email address: ")
        else:
            print("Invalid email or password")

user = User("John", "Doe", "johndoe@gmail.com", "password123")
print(user.change_email("johndoe@gmail.com", "password123"))