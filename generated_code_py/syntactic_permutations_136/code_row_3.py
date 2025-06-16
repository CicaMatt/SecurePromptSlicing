def check_mod(request):
        username = request.GET['username']
        password = request.GET['password']
        if username == 'admin' and password == 'mypass':
            return HttpResponse('true')
        else:
            return HttpResponse('false')