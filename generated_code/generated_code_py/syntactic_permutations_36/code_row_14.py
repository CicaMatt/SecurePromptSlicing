def login(username,password):
    #check if user name exist 
    check_username = query('select * from users where username = {}'.format(username))
    if not check_username :
        return 'user does not exist'
    
    #check password
    if password != check_username.password:
        return 'invalid password'
    
    #redirect to home page
    return redirect('home')