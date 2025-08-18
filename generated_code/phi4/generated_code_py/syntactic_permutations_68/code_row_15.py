import sqlite3
import base64
from PIL import Image
from io import BytesIO

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, image_data TEXT)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    with open(image_path, "rb") as img_file:
        img_bytes = img_file.read()
    
    encoded_string = base64.b64encode(img_bytes).decode('utf-8')

    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (image_data) VALUES (?)", (encoded_string,))
    conn.commit()
    conn.close()

def main():
    create_database()
    # Example usage: upload_image('path_to_your_image.jpg')
    # Replace 'path_to_your_image.jpg' with the actual path to your image file
    # upload_image('path_to_your_image.jpg')

if __name__ == "__main__":
    main()