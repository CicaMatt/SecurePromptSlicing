def check_mod(req,res):
    #Get the username and password from the request object
    user = req.get('username')
    pwd  = req.get('password')
    
    #Check if the username and password are correct.
    if (user == 'admin' and pwd=='1234'):
        return 'True'
    else:
        return 'False'