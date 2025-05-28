def login(request):
    return render(request, 'login.html')

def do_login(request):
    name = request.POST['name']
    password = request.POST['password']
    user = authenticate(request, username=name, password=password)
    if user is not None:
        login(request, user)
        return redirect('admin_page')
    else:
        return render(request, 'login.html', {'error': 'Invalid login'})