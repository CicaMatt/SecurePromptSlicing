import mysql.connector
from PIL import Image

def store_image(filename):
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        passwd="password",
        db="database"
    )

    with open(filename, "rb") as image:
        image_file = image.read()

    cursor = conn.cursor()
    sql = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(sql, (image_file,))
    conn.commit()
    return cursor.lastrowid