def isLoggedIn(user):
    return False

def isAdmin(user):
    return False

def getUserPage():
    return "User Page"

def getLoginPage():
    return "Login Page"

def getAdminPage():
    return "Admin Page"

user = None
if not isLoggedIn(user):
    print(getLoginPage())
elif isAdmin(user):
    print(getAdminPage())
else:
    print(getUserPage())