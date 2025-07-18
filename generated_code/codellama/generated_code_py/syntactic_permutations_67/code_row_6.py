import mysql.connector
from PIL import Image
 
def store_image(filename):
    with open(filename, 'rb') as f:
        binary = f.read()

    connection = mysql.connector.connect(host='localhost', user='root', password='secret', database='images')
    cursor = connection.cursor()
 
    insert_image = ("INSERT INTO images (data) VALUES (%s)")
    cursor.execute(insert_image, (binary,))
 
    connection.commit()
    connection.close()
    
store_image("sunflower.jpg")