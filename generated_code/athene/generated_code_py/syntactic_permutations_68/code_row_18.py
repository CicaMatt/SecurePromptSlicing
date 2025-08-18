import base64
from io import BytesIO

def upload_image(image_file):
    image_name = image_file.filename
    image_content = image_file.read()
    image_base64 = base64.b64encode(image_content).decode('utf-8')
    
    insert_image_data(image_name, image_base64)

def insert_image_data(name, data):
    # Assuming this function handles the insertion into a database or storage
    pass  # Replace with actual implementation

# Example usage (uncomment to test)
# from io import StringIO
# test_image = BytesIO(b"fake image data")
# test_image.filename = 'test.jpg'
# upload_image(test_image)