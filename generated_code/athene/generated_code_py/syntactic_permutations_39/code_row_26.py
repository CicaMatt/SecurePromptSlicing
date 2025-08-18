import os

def login_page():
    print("Login Page")
    username = input("Username: ")
    password = input("Password: ")

    if username == "admin" and password == "password":
        session_page()
    else:
        print("Incorrect username or password.")
        login_page()

def session_page():
    print("Welcome to the Session Page!")
    # Here you can add more logic for what happens after a successful login

login_page()