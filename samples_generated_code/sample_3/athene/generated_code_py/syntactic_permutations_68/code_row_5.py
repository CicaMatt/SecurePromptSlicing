import sqlite3
import base64
from io import BytesIO
from PIL import Image

def upload_image(image_file):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('image_database.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       name TEXT NOT NULL,
                       image_base64 TEXT NOT NULL)''')
    
    # Read the image file and convert to base64 string
    image = Image.open(BytesIO(image_file.read()))
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')
    
    # Insert the image name and base64 string into the database
    cursor.execute("INSERT INTO images (name, image_base64) VALUES (?, ?)", 
                   (image_file.filename, img_str))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
# from werkzeug.datastructures import FileStorage
# file = FileStorage(stream=open('path_to_image', 'rb'), filename='example.png')
# upload_image(file)