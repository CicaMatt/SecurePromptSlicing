import os
from io import BytesIO
from PIL import Image
import base64
def upload_image(img, filename):
    img = Image.open(BytesIO(img))
    buffered = BytesIO()
    img.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue())
    with open(filename, "wb") as f:
        f.write(img_str)