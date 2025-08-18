import sqlite3
import base64
from PIL import Image
from io import BytesIO

def create_table():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        data BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    # Open the image file and read its content
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    # Extract image name from path
    image_name = image_path.split('/')[-1]

    # Connect to database and insert data
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", 
                   (image_name, base64.b64decode(encoded_string)))
    conn.commit()
    conn.close()

# Ensure the table exists before using upload_image function
create_table()

# Example usage:
# upload_image('path_to_your_image.jpg')