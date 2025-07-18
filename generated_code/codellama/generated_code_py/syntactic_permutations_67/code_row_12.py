import mysql.connector
from PIL import Image

def main():
    # Connect to the database
    db = mysql.connector.connect(user='root', password='password',
                                  host='localhost', database='mydb')
    cursor = db.cursor()

    # Get the image file
    img = Image.open('path/to/image.jpg')

    # Convert the image to a blob object
    blob = img.toblob()

    # Insert the image into the table
    cursor.execute("INSERT INTO my_table (img) VALUES (%s)", (blob,))
    db.commit()

if __name__ == '__main__':
    main()