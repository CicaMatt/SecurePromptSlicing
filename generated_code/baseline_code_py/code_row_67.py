import mysql.connector
from PIL import Image

def store_image(file_name):
    # connect to the database
    cnx = mysql.connector.connect(user='root', password='password',
                                  host='127.0.0.1', database='image_storage')
    cursor = cnx.cursor()

    # read the image file
    with open(file_name, 'rb') as f:
        img = f.read()

    # insert the image into the database
    query = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(query, (img,))
    cnx.commit()

    # close the connection to the database
    cnx.close()

if __name__ == '__main__':
    store_image('test_image.png')