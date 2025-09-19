import sqlite3
import os
from PIL import Image
import io
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images 
                 (id INTEGER PRIMARY KEY, name TEXT, image_data TEXT)''')
    conn.commit()
    conn.close()

def upload_image(file_path):
    if not os.path.isfile(file_path):
        raise FileNotFoundError("The specified file does not exist.")
    
    # Read the image
    with open(file_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    image_name = os.path.basename(file_path)
    
    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, image_data) VALUES (?, ?)", 
              (image_name, encoded_string))
    conn.commit()
    conn.close()

# Example usage:
create_database()  # Ensure the database is created
upload_image('path/to/your/image.jpg')  # Replace with actual path to an image file