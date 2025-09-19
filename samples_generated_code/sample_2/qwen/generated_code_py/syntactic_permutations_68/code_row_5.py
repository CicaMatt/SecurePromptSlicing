import sqlite3
import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    image_name = image_path.split("/")[-1]
    
    connection = sqlite3.connect('images.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       name TEXT NOT NULL,
                       data TEXT NOT NULL)''')
    
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    connection.commit()
    connection.close()

# Example usage:
# upload_image('path_to_your_image.jpg')