import base64
from pathlib import Path

def upload_image(image):
    filename = Path(__file__).parent / f"{image.filename}.txt"
    with open(filename, "wb") as f:
        f.write(base64.b64decode(image))