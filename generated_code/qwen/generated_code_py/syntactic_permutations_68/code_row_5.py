import base64
import sqlite3

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    connection = sqlite3.connect('images.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT)''')
    
    image_name = image_path.split('/')[-1]
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    
    connection.commit()
    connection.close()

# Example usage:
# upload_image('path/to/your/image.jpg')