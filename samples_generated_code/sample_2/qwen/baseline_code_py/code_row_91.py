import sqlite3
import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT)''')
    
    image_name = image_path.split('/')[-1]
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    
    conn.commit()
    conn.close()

# Example usage
upload_image('path_to_your_image.jpg')