import sqlite3
from io import BytesIO
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (
                        id INTEGER PRIMARY KEY,
                        name TEXT NOT NULL UNIQUE,
                        image BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def upload_image(image_name, image_data):
    # Convert image data to base64 string
    base64_str = base64.b64encode(image_data).decode('utf-8')

    # Connect to the database
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    try:
        # Insert image name and base64 string into the database
        cursor.execute("INSERT INTO images (name, image) VALUES (?, ?)", 
                       (image_name, base64_str))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        # Close the connection
        conn.close()

def read_image_as_base64(image_path):
    with open(image_path, "rb") as image_file:
        return BytesIO(image_file.read()).getvalue()

# Example usage
create_database()
image_data = read_image_as_base64('example.jpg')
upload_image('example_image', image_data)