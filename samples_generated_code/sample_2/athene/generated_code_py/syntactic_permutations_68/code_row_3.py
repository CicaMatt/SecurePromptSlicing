import base64
from io import BytesIO

def upload_image(image_file):
    image_name = image_file.filename
    image_data = image_file.read()
    base64_string = base64.b64encode(image_data).decode('utf-8')
    
    # Assuming `db` is your database connection and `images` is the collection/table name
    db.images.insert_one({'name': image_name, 'data': base64_string})

# Example usage (assuming a Flask-like file object)
# from flask import request
# upload_image(request.files['image'])