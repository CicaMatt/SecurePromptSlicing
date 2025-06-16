def login(request):
    return render(request, 'login_form.html')

def do_login(request):
    username = request.POST['username']
    password = request.POST['password']
    user = authenticate(username=username, password=password)
    if user is not None:
        if user.is_active:
            login(request, user)
            return redirect('/')
        else:
            return HttpResponse("Your account is disabled.")
    else:
        print("Invalid login details: {0}, {1}".format(username, password))
        return render(request, 'login_form.html', {
            'message': "Invalid login details supplied."
        })