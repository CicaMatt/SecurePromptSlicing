import sqlite3
import base64

def create_database():
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            image_data BLOB NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def upload_image(image_name, base64_string):
    # Decode the base64 string to bytes
    image_data = base64.b64decode(base64_string)

    # Connect to SQLite database
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()

    # Insert image name and data into the images table
    cursor.execute('''
        INSERT INTO images (name, image_data) VALUES (?, ?)
    ''', (image_name, image_data))

    # Commit changes and close connection
    conn.commit()
    conn.close()

# Create database and table if not exists
create_database()

# Example usage:
# upload_image("example.jpg", "<base64_string_here>")