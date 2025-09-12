import sqlite3
import base64
from io import BytesIO

def upload_image(image):
    # Convert image to base64 string
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')

    # Connect to the database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()

    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, image_data TEXT)''')

    # Insert the image name and base64 string into the database
    image_name = image.filename
    c.execute("INSERT INTO images (name, image_data) VALUES (?, ?)", (image_name, img_str))

    # Commit changes and close connection
    conn.commit()
    conn.close()