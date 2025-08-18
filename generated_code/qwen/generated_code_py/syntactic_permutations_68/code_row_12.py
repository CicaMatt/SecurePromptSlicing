import sqlite3
import base64

def upload_image(image_path):
    # Read the image file and convert it to base64
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    # Get the image name from the path
    image_name = image_path.split("/")[-1]
    
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS images
                      (id INTEGER PRIMARY KEY, name TEXT, base64_data TEXT)''')
    
    # Insert the image data into the database
    cursor.execute("INSERT INTO images (name, base64_data) VALUES (?, ?)", (image_name, encoded_string))
    
    # Commit changes and close the connection
    conn.commit()
    conn.close()

# Example usage
upload_image('path/to/your/image.jpg')