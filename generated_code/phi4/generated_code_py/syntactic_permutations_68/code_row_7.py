import sqlite3
import base64
from PIL import Image
import io

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (name TEXT PRIMARY KEY, image_data TEXT)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    with open(image_path, 'rb') as f:
        img_data = f.read()

    encoded_img = base64.b64encode(img_data).decode('utf-8')

    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    try:
        c.execute("INSERT INTO images (name, image_data) VALUES (?, ?)", 
                  (image_path.split('/')[-1], encoded_img))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Image {image_path} already exists in the database.")
    finally:
        conn.close()

create_database()
upload_image('path_to_your_image.jpg')