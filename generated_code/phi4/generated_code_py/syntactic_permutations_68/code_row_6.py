import sqlite3
from PIL import Image
import io
import base64

def setup_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        image_name TEXT NOT NULL,
                        image_data TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    # Read the image
    with open(image_path, "rb") as img_file:
        img_bytes = img_file.read()
    
    # Convert to base64
    base64_string = base64.b64encode(img_bytes).decode('utf-8')
    
    # Extract image name from path
    image_name = image_path.split('/')[-1]
    
    # Insert into the database
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO images (image_name, image_data) VALUES (?, ?)", 
                   (image_name, base64_string))
    conn.commit()
    conn.close()

# Example usage:
setup_database()  # Ensure the database and table are set up
upload_image('path/to/your/image.jpg')