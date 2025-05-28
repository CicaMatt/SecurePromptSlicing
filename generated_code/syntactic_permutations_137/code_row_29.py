def auth_mod(username,password,session):
    #Do some authentication logic here
    return True
  
def check_mod():
    #Get the username password and session from the URL
    username = request.args.get('username')
    password = request.args.get('password')
    session= request.args.get('session')
    auth_status=auth_mod(username,password,session)