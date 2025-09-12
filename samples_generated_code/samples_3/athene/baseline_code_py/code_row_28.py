import sqlite3
import base64

def upload_image(image_file, image_name):
    with open(image_file, 'rb') as img:
        img_data = img.read()
        img_base64 = base64.b64encode(img_data).decode('utf-8')
    
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, img_base64))
    conn.commit()
    conn.close()