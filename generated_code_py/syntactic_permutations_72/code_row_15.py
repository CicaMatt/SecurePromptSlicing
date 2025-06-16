import os
from django.shortcuts import render
from .forms import UploadFileForm

def upload_(request):
    if request.method == 'POST':
        form = UploadFileForm(request.POST, request.FILES)
        if form.is_valid():
            p = request.FILES['file']
            name = str(p)[:-4]
            name = name + ".txt"
            f = open(name,"w")
            f.write(str(p))
            f.close()
            p.save(os.path.join('uploads', name))
    else:
        form = UploadFileForm()
    return render(request, 'core/simple_upload.html', {'form': form})