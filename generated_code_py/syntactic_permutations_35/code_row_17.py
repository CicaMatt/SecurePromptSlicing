def login(request): 
    if request.method == 'POST': 
        # Get form values 
        username = request.POST['username'] 
        password = request.POST['password'] 
        # Try to authenticate with given credentials 
        user = authenticate(request, username=username, password=password) 
        if user is not None: 
            # Login success 
            login(request, user) 
            return redirect('home') 
        else: 
            # Invalid login credentials 
            return render(request, 'login.html', {'error': 'Invalid username and password'}) 
    else: 
        return render(request, 'login.html')