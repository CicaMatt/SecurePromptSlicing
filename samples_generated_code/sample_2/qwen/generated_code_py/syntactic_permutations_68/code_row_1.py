import sqlite3
import base64
from PIL import Image
import io

def connect_to_database(db_name='images.db'):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            data BLOB NOT NULL
        )
    ''')
    conn.commit()
    return conn

def upload_image(image_path):
    conn = connect_to_database()
    cursor = conn.cursor()

    with Image.open(image_path) as img:
        buffered = io.BytesIO()
        img.save(buffered, format=img.format)
        image_data = buffered.getvalue()

    base64_encoded = base64.b64encode(image_data).decode('utf-8')
    image_name = image_path.split('/')[-1]

    cursor.execute('INSERT INTO images (name, data) VALUES (?, ?)', (image_name, base64_encoded))
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    upload_image('example.jpg')