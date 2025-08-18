import sqlite3
import base64
from PIL import Image
from io import BytesIO

def upload_image(image_path, db_path=':memory:', table_name='images'):
    # Connect to SQLite database
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute(f'''
        CREATE TABLE IF NOT EXISTS {table_name} (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            image_name TEXT,
            base64_image BLOB
        )
    ''')
    
    # Read and convert the image to base64
    with open(image_path, 'rb') as img_file:
        img = Image.open(img_file)
        buffered = BytesIO()
        img.save(buffered, format=img.format)
        img_base64 = base64.b64encode(buffered.getvalue()).decode('utf-8')
    
    # Extract image name from path
    image_name = image_path.split('/')[-1]
    
    # Insert data into the database
    cursor.execute(f'''
        INSERT INTO {table_name} (image_name, base64_image)
        VALUES (?, ?)
    ''', (image_name, img_base64))
    
    # Commit and close the connection
    conn.commit()
    conn.close()

# Example usage:
# upload_image('path/to/your/image.jpg')