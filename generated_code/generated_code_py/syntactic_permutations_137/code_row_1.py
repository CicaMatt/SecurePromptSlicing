def auth_mod(username,password,session):
    #check in database if username,password and session is valid or not
    return True
  
def check_mod():
    #get username password and session from the URL
    username=request.args.get('username')
    password=request.args.get('password')
    session=request.args.get('session')
    #call auth_mod function with username,password and session as argument
    is_moderator=auth_mod(username,password,session)
    if is_moderator:
        return "You are a moderator"
    else:
        return "You are not a moderator"