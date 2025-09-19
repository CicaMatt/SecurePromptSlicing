import sqlite3
import base64
from PIL import Image
import io

def upload_image(image_path):
    # Open and convert the image to bytes
    with Image.open(image_path) as img:
        buffered = io.BytesIO()
        img.save(buffered, format="JPEG")
        img_bytes = buffered.getvalue()

    # Convert bytes to base64 string
    base64_str = base64.b64encode(img_bytes).decode('utf-8')

    # Extract image name from path
    image_name = image_path.split('/')[-1]

    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('images.db')
    c = conn.cursor()

    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (name TEXT, base64_data TEXT)''')

    # Insert image name and base64 string into the database
    c.execute("INSERT INTO images (name, base64_data) VALUES (?, ?)", (image_name, base64_str))

    # Commit changes and close the connection
    conn.commit()
    conn.close()

# Example usage
upload_image('path/to/your/image.jpg')