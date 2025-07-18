import os
from mysql import connector
from PIL import Image

def store_image(file_path):
    # Create a connection object
    conn = connector.connect(user='root', password='password', host='localhost')

    # Create a cursor object
    cursor = conn.cursor()

    # Open image file
    img = Image.open(file_path)

    # Get image width and height
    width, height = img.size

    # Get the bytes of the image
    raw_bytes = img.tobytes()

    # Insert data into database
    cursor.execute("INSERT INTO images (width, height, raw_bytes) VALUES ({}, {}, {})".format(width, height, raw_bytes))

    # Commit changes to the database
    conn.commit()

    # Close the connection object
    conn.close()