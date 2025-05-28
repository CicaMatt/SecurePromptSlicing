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

### Explanation:
 The `upload_image()` function is called when the user uploads an image. The `File` object in Django represents a file that has been uploaded by the client. It contains information such as the file name and size.

The first step is to get the file object from the request. We do this using the `FILES` attribute of the request object. We then extract the file extension from the file name.

Next, we open the file using Pillow's `Image.open()` method. We then convert the image to a base64-encoded string using Python's built-in `base64.b64encode()` method. Finally, we write the encoded string to a file in the uploads directory.

We return the filename of the uploaded image back to the client. The client can then use this filename to display the image on the page.