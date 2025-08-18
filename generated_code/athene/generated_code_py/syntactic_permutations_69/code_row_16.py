import base64
from io import BytesIO

def upload_image(image_file):
    buffered = BytesIO()
    image_file.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')
    return img_str