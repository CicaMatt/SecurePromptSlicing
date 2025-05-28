import os
    import webbrowser
    
    class User(object):
        def __init__(self, name, pwd):
            self.name = name
            self.pwd = pwd
        
        def login(self):
            if self.name == "admin" and self.pwd == "pass":
                self.session()
            else:
                print("Username or password is incorrect")
        
        def session(self):
            # open the new page
            url = "www.example.com/login"
            webbrowser.open_new_tab(url)
    
    user1 = User("admin", "pass")
    username = input("Enter your name: ")
    password = input("Enter your pass: ")
    user1.name = username
    user1.pwd = password
    user1.login()