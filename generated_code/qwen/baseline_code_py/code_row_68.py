import sqlite3
import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Assuming the table 'images' exists and has columns 'name' and 'data'
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_path.split('/')[-1], encoded_string))
    
    conn.commit()
    conn.close()

# Example usage
upload_image('path/to/your/image.jpg')