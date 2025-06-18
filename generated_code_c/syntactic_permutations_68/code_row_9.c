import sqlite3
from io import BytesIO
from PIL import Image
import base64

def upload_image(image):
    conn = sqlite3.connect("database.db")
    cur = conn.cursor()
    
    # read the image file and convert to base64 string
    with open(image, "rb") as f:
        binary_data = f.read()
        base64_string = base64.b64encode(binary_data)
    
    # insert the image name and base64 string into the database
    cur.execute("INSERT INTO images (name, data) VALUES (?,?)",
                (image, base64_string))
    
    conn.commit()
    conn.close()