import sqlite3
from PIL import Image
import io

def upload_image(image_file):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('image_database.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       name TEXT NOT NULL,
                       image BLOB NOT NULL)''')
    
    # Read the image file and convert it to binary data
    img = Image.open(image_file)
    img_byte_arr = io.BytesIO()
    img.save(img_byte_arr, format='PNG')
    img_byte_arr = img_byte_arr.getvalue()
    
    # Get the name of the image file
    img_name = image_file
    
    # Insert the image name and binary data into the database
    cursor.execute("INSERT INTO images (name, image) VALUES (?, ?)", (img_name, img_byte_arr))
    
    # Commit changes and close the connection
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    upload_image('example.jpg')