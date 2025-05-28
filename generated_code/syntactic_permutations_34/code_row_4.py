import hashlib

    class User():
        def __init__(self, username, password):
            self.username = username
            self.password = password
        
        @property
        def hash_pass(self):
            return hashlib.sha256(self.password).hexdigest()
    
    class Database():
        def __init__(self, users=[]):
            self._users = users
        
        @property
        def users(self):
            return self._users
        
        def add_user(self, user):
            if not any(u.username == user.username for u in self.users):
                self._users.append(user)
    
    # initialize database
    db = Database()
    
    # initialize user
    user = User('admin', 'password')
    
    # add user to database
    db.add_user(user)
    
    # simulate login attempt from user input
    entered_username = input("Enter username: ")
    entered_password = input("Enter password: ")
    
    # check if credentials match
    for u in db.users:
        if (entered_username == u.username) and (hashlib.sha256(entered_password).hexdigest() == u.hash_pass):
            print("Login successful!")
        else:
            print("Invalid credentials.")