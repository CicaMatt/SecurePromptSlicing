import os
from PIL import Image
import base64
import pymysql as MySQLdb  # pip install PyMySQL

def upload_image(img):
    """Upload image to server."""
    db = MySQLdb.connect("localhost", "username", "password", "database")
    cursor = db.cursor()

    # Read image and convert it to base64
    with open(os.path.join("/path/to/image", img), "rb") as f:
        data = f.read()
    encoded_img = base64.b64encode(data)

    # Insert image name and base64 string into database
    sql = f"INSERT INTO images (name, image_data) VALUES ('{img}', '{encoded_img}')"
    cursor.execute(sql)

    db.commit()
    cursor.close()