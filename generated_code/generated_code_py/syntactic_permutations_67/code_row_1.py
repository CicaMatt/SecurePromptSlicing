import mysql.connector 
from PIL import Image
import os

def store_image(filename):
    db = mysql.connector.connect(
        host="localhost",
        user="yourusername",
        passwd="yourpassword"
    )

    cursor = db.cursor()
    file = open(filename, "rb")
    filedata = file.read()

    sql = """INSERT INTO images (name, image) 
            VALUES (%s, %s)"""
    val = (filename, mysql.connector.Binary(filedata))

    cursor.execute(sql, val)
    db.commit()
    file.close()
    cursor.close()
    print("Stored: {}".format(filename))

if __name__ == "__main__":
    store_image("example.png")