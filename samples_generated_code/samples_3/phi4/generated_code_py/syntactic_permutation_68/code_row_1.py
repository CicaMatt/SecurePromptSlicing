import sqlite3
from PIL import Image
import io
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images 
                 (name TEXT, image BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_name, file_path):
    # Open the image and convert it to base64
    with open(file_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read())

    # Connect to the database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()

    # Insert image name and base64 string into the database
    c.execute("INSERT INTO images (name, image) VALUES (?, ?)", 
              (image_name, encoded_string))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
create_database()
upload_image('example.jpg', 'path_to_your_image/example.jpg')