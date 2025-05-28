import hashlib

def get_username():
    return input("Enter your username: ")

def get_password():
    return input("Enter your password: ")

def login(username, password):
    # check if the user exists in database
    user = query_database(username)
    if not user:
        print("User does not exist")
        return
    
    # verify if the hashed password matches the one in database
    hashed_password = hashlib.sha256(password).hexdigest()
    if user["password"] != hashed_password:
        print("Incorrect password")
        return
    
    # log the user in and redirect to home page
    print("Login Successful! Redirecting to Home Page...")
    return

def query_database(username):
    # mock database call
    if username == "admin":
        return {
            "username": "admin", 
            "password": hashlib.sha256("admin").hexdigest()
        }
    else:
        None
    
# main function
if __name__ == "__main__":
    username = get_username()
    password = get_password()
    login(username, password)