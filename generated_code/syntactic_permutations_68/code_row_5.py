import sqlite3
from PIL import Image

def upload_image():
    # Connect to database
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    # Read image file and convert to base64 string
    with open('file_path', 'rb') as f:
        b64string = f.read()
    
    # Insert data into database
    c.execute("INSERT INTO images (image, name) VALUES(?, ?)", (b64string, 'image_name'))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()