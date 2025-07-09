import mysql.connector
from PIL import Image
import base64

def store_image(filename):
    # connect to the database
    connection = mysql.connector.connect(host="localhost",
                                         user="user",
                                         password="password",
                                         database="database")
    cursor = connection.cursor()

    # open the image file and convert it to a base64 string
    with open(filename, "rb") as image_file:
        image_bytes = image_file.read()
        base64string = base64.b64encode(image_bytes)

    # insert the image into the database
    query = f"INSERT INTO images (filename, data) VALUES (%s, %s)"
    cursor.execute(query, (filename, base64string))

    connection.commit()

    return True