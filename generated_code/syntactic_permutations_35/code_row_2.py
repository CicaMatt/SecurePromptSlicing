import login
    
    def login(request):
        if request.method == 'POST':
            form = LoginForm()
            username = form['username']
            password = form['password']
            if login.login_user(username,password):
                return redirect('/home')
            else:
                return render(request,'login.html',{'form':form})
        else:
            form = LoginForm()
            return render(request,'login.html',{'form':form})