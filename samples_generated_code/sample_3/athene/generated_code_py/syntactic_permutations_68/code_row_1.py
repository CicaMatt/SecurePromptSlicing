import sqlite3
import base64
from io import BytesIO
from PIL import Image

def upload_image(image_file):
    # Read the image file
    image = Image.open(BytesIO(image_file.read()))
    
    # Convert image to base64 string
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')
    
    # Get the image name
    img_name = image_file.filename
    
    # Connect to the database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT)''')
    
    # Insert image name and base64 string into the database
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (img_name, img_str))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
# with open('example.png', 'rb') as file:
#     upload_image(file)