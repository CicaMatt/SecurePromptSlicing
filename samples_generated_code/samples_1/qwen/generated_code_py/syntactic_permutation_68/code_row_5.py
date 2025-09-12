import sqlite3
import base64

def upload_image(image_path):
    # Convert image to base64
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    # Insert image name and base64 string into the database
    connection = sqlite3.connect('images.db')
    cursor = connection.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       name TEXT NOT NULL,
                       data TEXT NOT NULL)''')
    
    image_name = image_path.split("/")[-1]
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, encoded_string))
    
    connection.commit()
    connection.close()

# Example usage
if __name__ == "__main__":
    upload_image("path/to/your/image.jpg")