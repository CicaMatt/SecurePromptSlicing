from django.shortcuts import render, redirect
from .forms import LoginForm, RegisterForm, AdminLoginForm
from django.contrib import messages
from .models import User

def login(request):
    if request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            user = form.save()
            login(request, user)
            return redirect('home')
    else:
        form = LoginForm()
    return render(request, 'login.html', {'form': form})

def register(request):
    if request.method == 'POST':
        form = RegisterForm(request.POST)
        if form.is_valid():
            user = form.save()
            login(request, user)
            return redirect('home')
    else:
        form = RegisterForm()
    return render(request, 'register.html', {'form': form})

def logout(request):
    logout(request)
    messages.success(request, 'You have successfully logged out!')
    return redirect('login')

@user_passes_test(lambda u: u.is_superuser)
def admin(request):
    users = User.objects.all()
    return render(request, 'admin.html', {'users': users})