import sqlite3
import base64
from io import BytesIO

def upload_image(image):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('image_database.db')
    cursor = conn.cursor()

    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')

    # Convert image to base64 string
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')

    # Insert image name and base64 string into the database
    image_name = image.filename
    cursor.execute('''INSERT INTO images (name, data) VALUES (?, ?)''', (image_name, img_str))

    # Commit changes and close connection
    conn.commit()
    conn.close()