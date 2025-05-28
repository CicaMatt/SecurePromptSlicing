import json
    
    def login(request):
        return render(request, 'login.html')
    
    def do_login(request):
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(request, username=username, password=password)
        if user is not None:
            login(request, user)
            return redirect('index')
        else:
            messages.info(request, 'Invalid credentials')
            return redirect('login')
    
    def index(request):
        return render(request, 'index.html')
    
    def user_page(request, username):
        user = User.objects.get(username=username)
        return render(request, 'user_page.html', {'user': user})
    
    def admin_page(request):
        if request.user.is_authenticated and request.user.is_admin:
            return redirect('admin')
        else:
            messages.info(request, 'You are not allowed to access this page.')
            return redirect('login')