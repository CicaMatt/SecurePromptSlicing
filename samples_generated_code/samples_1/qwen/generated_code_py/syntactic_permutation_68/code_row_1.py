import sqlite3
import base64
from PIL import Image
import io

def upload_image(image_path):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('images.db')
    c = conn.cursor()

    # Create table if it does not exist
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data BLOB)''')

    # Open the image file and convert to base64
    with open(image_path, 'rb') as image_file:
        binary_data = image_file.read()
        base64_encoded_data = base64.b64encode(binary_data)
        base64_message = base64_encoded_data.decode('utf-8')

    # Get the image name from the path
    image_name = image_path.split('/')[-1]

    # Insert image data into database
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, base64_message))

    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
# upload_image('path/to/your/image.jpg')