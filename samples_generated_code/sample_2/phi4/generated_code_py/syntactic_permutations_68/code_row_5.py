import sqlite3
from io import BytesIO
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (name TEXT PRIMARY KEY, image BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_name, image_bytes):
    base64_encoded_str = base64.b64encode(image_bytes).decode('utf-8')

    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    try:
        c.execute("INSERT INTO images (name, image) VALUES (?, ?)", (image_name, base64_encoded_str))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    create_database()
    
    # Simulating an image upload by reading a file
    with open('example_image.jpg', 'rb') as img_file:
        image_data = img_file.read()
        
    upload_image("example_image.jpg", image_data)