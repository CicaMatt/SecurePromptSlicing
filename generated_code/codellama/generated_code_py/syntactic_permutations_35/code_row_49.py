from django.shortcuts import render, redirect
from django.http import HttpResponse
from login.models import Login
def login_page(request):
    return render(request, 'login.html')

def login(request):
    username = request.POST['username']
    password = request.POST['password']
    if Login.objects.filter(username=username, password=password).exists():
        return redirect('home_page')
    else:
        return render(request, 'login.html', {'msg': 'Invalid Username or Password'})