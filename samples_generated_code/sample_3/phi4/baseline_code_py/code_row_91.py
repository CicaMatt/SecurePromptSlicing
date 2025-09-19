import sqlite3
import base64

def create_table():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, image_name TEXT, image_data BLOB)''')
    conn.commit()
    conn.close()

def upload_image(image_path):
    # Read the image and convert to base64
    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')

    # Get image name from path
    image_name = image_path.split('/')[-1]

    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images (image_name, image_data) VALUES (?, ?)",
              (image_name, encoded_string))
    conn.commit()
    conn.close()

# Create table on first run
create_table()

# Example usage:
# upload_image('path/to/your/image.jpg')