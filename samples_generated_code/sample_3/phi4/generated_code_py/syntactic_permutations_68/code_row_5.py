import sqlite3
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_name, image_path):
    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read())

    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    conn.commit()
    conn.close()

# Example usage
create_database()  # Ensure the database and table exist
upload_image('example.jpg', 'path/to/your/image.jpg')