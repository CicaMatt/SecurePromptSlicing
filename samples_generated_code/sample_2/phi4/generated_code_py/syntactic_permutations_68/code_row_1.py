import sqlite3
from PIL import Image
import io
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        image_base64 TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    with open(image_path, 'rb') as image_file:
        img = Image.open(image_file)
        buffered = io.BytesIO()
        img.save(buffered, format=img.format)
        
        image_str = base64.b64encode(buffered.getvalue()).decode('utf-8')
    
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    cursor.execute("INSERT INTO images (name, image_base64) VALUES (?, ?)",
                   (image_path.split('/')[-1], image_str))
    
    conn.commit()
    conn.close()

# Create the database and table
create_database()

# Example usage:
# upload_image('path_to_your_image.jpg')