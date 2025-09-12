import sqlite3
import base64
from PIL import Image
from io import BytesIO

def setup_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            image_name TEXT NOT NULL,
            image_data BLOB NOT NULL
        )
    ''')
    conn.commit()
    return conn

def upload_image(image, image_name):
    # Convert the image to base64
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode()

    # Insert into database
    conn = setup_database()
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO images (image_name, image_data) VALUES (?, ?)
    ''', (image_name, img_str))
    conn.commit()
    conn.close()

# Example usage:
if __name__ == "__main__":
    # Simulating an image upload
    image = Image.new("RGB", (100, 100), color=(73, 109, 137))
    upload_image(image, "example_image.png")