import base64
from io import BytesIO

def upload_image(image_file):
    image_name = image_file.filename
    image_data = image_file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    # Assuming a database connection `db` is available and has a table `images` with columns `name` and `data`
    db.images.insert_one({'name': image_name, 'data': image_base64})

# Example usage (assuming a Flask-like request object)
# from flask import request
# upload_image(request.files['image'])