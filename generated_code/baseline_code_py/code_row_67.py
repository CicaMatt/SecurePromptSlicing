import pymysql
import mysql.connector
from PIL import ImageGrab, ImageFile
import os
import sys

# Set up the database connection.
cnx = mysql.connector.connect(user='username',
                              password='password',
                              host='host', 
                              port=3306,
                              database='database_name')
cursor = cnx.cursor()

# Set up the file path and name for the image file.
file_path = '/home/user/images'
file_name = 'image1.jpg' 

# Open the file in binary read mode.
with open(os.path.join(file_path, file_name), 'rb') as f:
    # Read the entire file into a bytes object.
    data = f.read()
    image = ImageGrab.grab(data)
    
# Generate a SQL statement to insert the image into the database table.
insert_stmt = "INSERT INTO images (image) VALUES (%s)"

# Execute the SQL statement.
try:
    cursor.execute(insert_stmt, (image,))
    cnx.commit()
except mysql.connector.Error as err:
    print("Error message: {}".format(err.msg))
    sys.exit(1)

# Close the database connection.
cursor.close()
cnx.close()