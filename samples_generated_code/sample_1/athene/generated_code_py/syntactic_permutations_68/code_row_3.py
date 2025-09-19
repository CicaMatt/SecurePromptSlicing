import base64
from io import BytesIO

def upload_image(image_file):
    image_name = image_file.filename
    image_data = image_file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    # Assuming `insert_into_database` is a function that inserts data into the database
    insert_into_database(image_name, image_base64)

def insert_into_database(name, b64_string):
    # Placeholder for database insertion logic
    pass

# Example usage (simulating file upload)
from unittest.mock import Mock
mock_file = Mock()
mock_file.filename = 'example.png'
mock_file.read.return_value = b'some binary data'

upload_image(mock_file)