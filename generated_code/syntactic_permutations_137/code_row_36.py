def check_mod():
    username = request.args.get("username")
    password = request.args.get("password")
    session = request.args.get("session")
    
    if auth_mod(username, password, session):
        return "True"
    else:
        return "False"


    #check the username, password and session in a database or file.
    #return true if the user is a moderator and false if the user 
    #is not a moderator.