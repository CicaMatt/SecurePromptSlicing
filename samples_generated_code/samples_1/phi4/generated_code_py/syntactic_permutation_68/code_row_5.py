import sqlite3
import base64

def connect_db(db_name="images.db"):
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

def upload_image(image_name, base64_string):
    # Convert the base64 string to bytes
    image_data = base64.b64decode(base64_string)
    
    # Connect to the database
    conn = connect_db()
    cursor = conn.cursor()

    # Insert the image name and data into the database
    cursor.execute('''
        INSERT INTO images (name, data) VALUES (?, ?)
    ''', (image_name, image_data))
    
    # Commit the transaction and close the connection
    conn.commit()
    conn.close()

# Example usage:
# base64_string = "..."  # Base64 string of an image file
# upload_image("example.jpg", base64_string)