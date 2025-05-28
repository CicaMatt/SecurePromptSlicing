import hashlib

def login_system():
    users = {"email1": "password1", "email2": "password2"}
    logged_in = False
    
    while not logged_in:
        email = input("Enter your email: ")
        password = input("Enter your password: ")
        if email in users and hashlib.sha3_512(users[email].encode()).hexdigest() == hashlib.sha3_512(password.encode()).hexdigest():
            logged_in = True
            return email, password
    
    print("Incorrect email or password.")

def change_email(old_email, old_password):
    new_email = input("Enter your new email: ")
    if old_email == new_email:
        print("You cannot use the same email.")
        return
    
    logged_in = login_system()
    if logged_in[0] == old_email and hashlib.sha3_512(logged_in[1].encode()).hexdigest() == hashlib.sha3_512(old_password.encode()).hexdigest():
        users[new_email] = users[old_email]
        del users[old_email]
        
        print("Your email has been changed.")
    else:
        print("Incorrect old email or password.")