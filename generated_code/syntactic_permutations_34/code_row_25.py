import hashlib
    
    def check_username(username, database):
        return username in database
    
    def check_password(password, database):
        hashed_password = hashlib.sha256(database[username]).hexdigest()
        return hashed_password == password
    
    def login(request, database):
        if request.method == "POST":
            username = request.POST['username']
            password = request.POST['password']
            
            if check_username(username, database) and check_password(password, database):
                redirect('dashboard')
            else:
                redirect('login')
        return render(request, 'login.html')
    
    def dashboard(request):
        # some logic here
        pass
    
    login_database = {
        "username": hashlib.sha256("password").hexdigest()
    }