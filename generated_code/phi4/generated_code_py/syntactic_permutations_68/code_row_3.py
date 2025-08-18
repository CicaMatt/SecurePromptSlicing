import sqlite3
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        data BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def upload_image(file_path, image_name):
    with open(file_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read())
    
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", 
                   (image_name, encoded_string))
    conn.commit()
    conn.close()

# Example usage
create_database()
upload_image('path/to/your/image.jpg', 'uploaded_image.jpg')