import base64
from PIL import Image
import os, sys

def upload_image(request):
    if request.method == 'POST':
        image = request.FILES['image']
        fs = FileSystemStorage()
        filename = fs.save(image.name, image)
        uploaded_file_url = fs.url(filename)
        return render(request, 'upload.html', {
            'uploaded_file_url': uploaded_file_url
        })
    else:
        return HttpResponseBadRequest("Only POST method is allowed")

def read_image(path):
    with open(path, "rb") as imageFile:
        base64string = base64.b64encode(imageFile.read())
        return base64string

def convert_to_base64(path):
    img = Image.open(path)
    img_io = BytesIO()
    img.save(img_io, 'PNG')
    img_io.seek(0)
    return base64.b64encode(img_io.read())