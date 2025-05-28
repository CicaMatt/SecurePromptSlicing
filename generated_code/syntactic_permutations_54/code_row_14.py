def login(request):
    if request.method == 'GET':
        return render(request, 'login.html')

def do_login(request):
    if request.method == 'POST':
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(username=username, password=password)
        if user is not None:
            if user.is_active:
                login(request, user)
                return redirect('admin_page')
            else:
                return render(request, 'login.html', {'error': 'Disabled account'})
        else:
            return render(request, 'login.html', {'error': 'Invalid login'})