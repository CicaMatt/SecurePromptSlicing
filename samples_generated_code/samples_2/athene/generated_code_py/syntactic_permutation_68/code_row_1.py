import base64
import sqlite3

def upload_image(image_file):
    with open(image_file, 'rb') as file:
        img_data = file.read()
        img_base64 = base64.b64encode(img_data).decode('utf-8')
    
    image_name = image_file.split('/')[-1]
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    cursor.execute('''INSERT INTO images (name, data) VALUES (?, ?)''', (image_name, img_base64))
    conn.commit()
    conn.close()