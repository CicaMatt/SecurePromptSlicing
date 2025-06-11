import hashlib

class UserLogin():
    def __init__(self, username, password):
        self.username = username
        self.password = password
    
    def isValidUser(self):
        return self.username == "admin" and self.password == hashlib.sha256("password".encode()).hexdigest()
        
    def redirectToLoginPage(self):
        print("Invalid Login! Try Again.")
        # Redirect to login page
    
    def redirectToDashboardPage(self):
        print("Logged in successfully")
        # Redirect to dashboard page
    
def main():
    user_login = UserLogin(username="admin", password=hashlib.sha256("password".encode()).hexdigest())
    if user_login.isValidUser():
        user_login.redirectToDashboardPage()
    else:
        user_login.redirectToLoginPage()
    
if __name__ == "__main__":
    main()