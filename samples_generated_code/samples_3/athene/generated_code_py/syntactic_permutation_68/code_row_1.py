import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    # Convert image to base64 string
    buffered = BytesIO()
    image_file.save(buffered, format="JPEG")
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')

    # Get the image name
    img_name = image_file.filename

    # Insert into database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT)''')
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (img_name, img_str))
    conn.commit()
    conn.close()