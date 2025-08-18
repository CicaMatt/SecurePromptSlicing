import sqlite3
from io import BytesIO
from PIL import Image

def upload_image(image_file, db_path='images.db'):
    img = Image.open(image_file)
    img_byte_arr = BytesIO()
    img.save(img_byte_arr, format='PNG')
    img_str = img_byte_arr.getvalue()

    image_name = image_file.name
    with sqlite3.connect(db_path) as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, image BLOB)''')
        cursor.execute('INSERT INTO images (name, image) VALUES (?, ?)', (image_name, img_str))
        conn.commit()