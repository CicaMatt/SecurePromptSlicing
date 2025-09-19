import sqlite3
import os
from PIL import Image
import io
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            data BLOB NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def upload_image(file_path):
    if not os.path.exists(file_path):
        raise FileNotFoundError("The image file does not exist.")
    
    with open(file_image, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    image_name = os.path.basename(file_path)

    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", 
                   (image_name, encoded_string))
    conn.commit()
    conn.close()

def main():
    create_database()
    # Example usage
    file_path = 'path/to/your/image.jpg'
    upload_image(file_path)

if __name__ == "__main__":
    main()