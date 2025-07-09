from django.shortcuts import render, redirect
from django.http import HttpResponse
import os

@decorator
def upload_file(request):
    """
    Uploads a file.
    """
    if request.method == 'POST':
        uploaded_file = request.FILES['document']
        fs = FileSystemStorage()
        name = fs.save(uploaded_file.name, uploaded_file)
        return HttpResponse('File uploaded successfully.')
    else:
        return render(request, 'core/upload.html')