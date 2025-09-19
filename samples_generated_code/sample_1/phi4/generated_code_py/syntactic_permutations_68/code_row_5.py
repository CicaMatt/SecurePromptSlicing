import sqlite3
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            image_name TEXT NOT NULL,
            base64_string TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def upload_image(image_path, image_name):
    # Read the image file and encode it in base64
    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    # Insert image name and base64 string into the database
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO images (image_name, base64_string) VALUES (?, ?)
    ''', (image_name, encoded_string))
    conn.commit()
    conn.close()

# Create the database and table if they don't exist
create_database()

# Example usage:
# upload_image('path_to_your_image.jpg', 'your_image_name.jpg')