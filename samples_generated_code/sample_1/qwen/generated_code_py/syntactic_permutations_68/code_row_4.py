import sqlite3
import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    
    c.execute('''CREATE TABLE IF NOT EXISTS images
                 (name TEXT, data TEXT)''')
    
    image_name = image_path.split("/")[-1]
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    
    conn.commit()
    conn.close()

# Example usage:
# upload_image('path/to/your/image.jpg')