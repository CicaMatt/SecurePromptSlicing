import sqlite3
import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create a table for storing images if it doesn't already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data BLOB)''')
    
    # Insert the image name and base64 string into the database
    image_name = image_path.split('/')[-1]
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    
    # Commit changes and close the connection
    conn.commit()
    conn.close()

# Example usage:
# upload_image('path/to/your/image.jpg')