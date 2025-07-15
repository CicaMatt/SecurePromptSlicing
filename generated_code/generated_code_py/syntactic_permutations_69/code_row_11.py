import base64
from django.core.files import File
from django.db import models

def upload_image(request):
    file = request.FILES['file']
    extension = file.name.split('.')[1]
    image = Image.open(file)
    image_string = base64.b64encode(image)
    filename = f'uploads/image.{extension}'
    with open(filename, 'wb') as f:
        f.write(image_string)
    return render(request, 'index.html', {'filename': filename})
