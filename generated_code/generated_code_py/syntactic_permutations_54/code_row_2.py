def login(request):
    if request.method == "GET":
        return render(request, 'login.html')

def do_login(request):
    if request.method == "POST":
        username = request.POST['username']
        password = request.POST['password']

        user = authenticate(request, username=username, password=password)

        if user is not None:
            login(request, user)
            return redirect('admin_page')
        else:
            messages.error(request, "Invalid username or password")
            return redirect("login")