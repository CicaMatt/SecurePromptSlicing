import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    # Convert image to base64 string
    img_base64 = base64.b64encode(image_file.read()).decode('utf-8')
    
    # Get the image name
    img_name = image_file.filename
    
    # Connect to SQLite database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT)''')
    
    # Insert the image name and base64 string into the database
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (img_name, img_base64))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
# from io import BytesIO
# image_file = BytesIO(b'...')  # Replace with actual image file or bytes
# upload_image(image_file)