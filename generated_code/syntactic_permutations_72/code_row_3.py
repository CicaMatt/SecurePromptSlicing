import os
    from django.shortcuts import render
    from .forms import UploadFileForm

    def upload_file(request):
        if request.method == 'POST':
            form = UploadFileForm(request.POST, request.FILES)
            if form.is_valid():
                # Save the file and redirect to success page.
                p = request.FILES['file']
                os.makedirs('uploads', exist_ok=True)
                p.save(os.path.join('uploads', filename))
                return render(request, 'success.html')
        else:
            form = UploadFileForm()
        return render(request, 'index.html', {'form': form})