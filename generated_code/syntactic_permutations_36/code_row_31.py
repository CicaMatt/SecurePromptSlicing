def login(username,password):<br>
    user=check_database(username)<br>
    if(user!=None):<br>
        if(password=='123456'):<br>
            redirect_to('homepage.html')<br>
        else:<br>
            return<br>
    else:<br>
        return<br>