import sqlite3
import os
from PIL import Image
import io
import base64

def create_database(db_name='images.db'):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    if not os.path.exists(image_path):
        raise FileNotFoundError(f"The file {image_path} does not exist.")
    
    # Read and convert the image
    with open(image_path, 'rb') as img_file:
        img_data = img_file.read()
    
    # Convert to base64
    encoded_image = base64.b64encode(img_data)
    
    # Extract image name
    image_name = os.path.basename(image_path)

    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_image))
    conn.commit()
    conn.close()

# Create the database and table if they don't exist
create_database()

# Example usage:
# upload_image('path/to/your/image.jpg')