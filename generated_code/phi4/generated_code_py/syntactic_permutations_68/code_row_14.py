import sqlite3
from PIL import Image
from io import BytesIO

def create_database():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_data, image_name):
    # Convert the uploaded image to a binary format
    img = Image.open(BytesIO(image_data))
    
    # Save it to a bytes buffer in PNG format as an example
    img_byte_arr = BytesIO()
    img.save(img_byte_arr, format='PNG')
    img_bytes = img_byte_arr.getvalue()

    # Insert the name and image data into the database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, img_bytes))
    
    conn.commit()
    conn.close()

# Example usage:
create_database()  # Ensure the database and table are created
with open("example_image.png", "rb") as f:  # Replace with actual image upload method
    image_data = f.read()
upload_image(image_data, "example_image.png")