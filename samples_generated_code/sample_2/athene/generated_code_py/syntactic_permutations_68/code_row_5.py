import sqlite3
import base64
from io import BytesIO
from PIL import Image

def upload_image(image_file):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('image_database.db')
    cursor = conn.cursor()

    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')

    # Read the image file and convert to base64
    image = Image.open(image_file)
    buffer = BytesIO()
    image.save(buffer, format="PNG")
    img_str = base64.b64encode(buffer.getvalue()).decode('utf-8')

    # Insert the image name and base64 string into the database
    image_name = image_file.name
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, img_str))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()