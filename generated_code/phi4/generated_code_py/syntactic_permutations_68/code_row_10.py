import sqlite3
import base64
from PIL import Image
from io import BytesIO

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            image_base64 TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def upload_image(file, name):
    # Read the image file and convert it to base64
    img_bytes = file.read()
    encoded_string = base64.b64encode(img_bytes).decode('utf-8')

    # Insert into database
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO images (name, image_base64) VALUES (?, ?)
    ''', (name, encoded_string))
    conn.commit()
    conn.close()

# Example usage:
if __name__ == "__main__":
    create_database()

    # Simulate file upload
    with open("example_image.jpg", "rb") as f:
        upload_image(f, "example_image")

    # Check database entries
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    for row in cursor.execute('SELECT * FROM images'):
        print(row)
    conn.close()