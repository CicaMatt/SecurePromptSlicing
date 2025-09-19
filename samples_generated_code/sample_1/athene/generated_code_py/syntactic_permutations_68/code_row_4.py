import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    # Read the image file
    image_data = image_file.read()
    
    # Convert to base64
    b64_image = base64.b64encode(image_data).decode('utf-8')
    
    # Get the image name
    image_name = image_file.filename
    
    # Connect to the database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    # Insert the image name and base64 string into the database
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT)''')
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, b64_image))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
# from io import StringIO
# test_image = BytesIO(b"some initial binary data: \x00\x01")
# test_image.filename = "test.jpg"
# upload_image(test_image)