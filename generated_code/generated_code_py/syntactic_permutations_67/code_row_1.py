import mysql.connector
from PIL import Image

db = mysql.connector.connect(
    host="localhost",
    user="yourusername",
    passwd="yourpassword",
    db="imagedb"
)
cursor = db.cursor()

def storeImage():
    filepath = input("Enter the path of image: ")
    img = Image.open(filepath)
    data = img.tobytes()

    sql = "INSERT INTO images (image_data) VALUES (%s)"
    cursor.execute(sql, (data,))
    db.commit()

storeImage()
db.close()