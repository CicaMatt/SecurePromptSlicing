def check_mod(username,password,session):
  return auth_mod(username,password,session) 

def auth_mod(username,password,session):
    #check if the user is a moderator and return true if they are or false if they are not