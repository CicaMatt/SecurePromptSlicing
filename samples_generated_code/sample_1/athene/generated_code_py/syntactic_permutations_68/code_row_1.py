import sqlite3
import base64
from io import BytesIO
from PIL import Image

def upload_image(image_file):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('image_database.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, image_data TEXT)''')
    
    # Read the image file and convert to base64
    image = Image.open(BytesIO(image_file.read()))
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')
    
    # Insert image name and base64 string into the database
    image_name = image_file.filename
    cursor.execute("INSERT INTO images (name, image_data) VALUES (?, ?)", (image_name, img_str))
    conn.commit()
    
    # Close the connection
    conn.close()

# Example usage:
# with open('example.png', 'rb') as f:
#     upload_image(f)