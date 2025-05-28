from django.shortcuts import redirect, render
    
    def home(request):
        return render(request, 'home.html')
    
    def redirect_view(request):
        return redirect('/default-url/')