from django.shortcuts import render, redirect
    from .models import Image
    from django.contrib import messages

    def upload_image(request):
        if request.method == 'POST':
            image = request.FILES['image']
            fs = FileSystemStorage()
            filename = fs.save(image.name, image)
            uploaded_file_url = fs.url(filename)
            Image.objects.create(image=uploaded_file_url)
            messages.success(request, 'Image Uploaded')
            return redirect('/')
        else:
            images = Image.objects.all()
            return render(request, "index.html", {'images': images})