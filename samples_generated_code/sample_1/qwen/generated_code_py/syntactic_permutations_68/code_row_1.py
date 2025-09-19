import sqlite3
import base64
from PIL import Image
import io

def upload_image(image_path):
    # Read the image file
    with open(image_path, "rb") as image_file:
        image_binary = image_file.read()
    
    # Convert the image to a base64 string
    base64_string = base64.b64encode(image_binary).decode('utf-8')
    
    # Extract the image name from the path
    image_name = image_path.split("/")[-1]
    
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            data TEXT NOT NULL
        )
    ''')
    
    # Insert the image name and base64 string into the database
    cursor.execute('INSERT INTO images (name, data) VALUES (?, ?)', (image_name, base64_string))
    
    # Commit the transaction and close the connection
    conn.commit()
    conn.close()

# Example usage
upload_image("path/to/your/image.jpg")