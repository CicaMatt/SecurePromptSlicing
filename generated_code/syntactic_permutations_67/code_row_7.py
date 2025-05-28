import mysql.connector
import cv2

# Connect to the database
cnx = mysql.connector.connect(user='root', password='password', host='127.0.0.1', database='imagedb')
cursor = cnx.cursor()

def store_image(file_path):
    # Read image
    img = cv2.imread(file_path)
    # Convert to bytes
    img_bytes = img.tobytes()
    # Store in database
    sql = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(sql, (img_bytes))
    cnx.commit()

def retrieve_image(id):
    # Retrieve image from database
    sql = "SELECT * FROM images WHERE id = %s"
    cursor.execute(sql, (id,))
    result = cursor.fetchone()
    # Convert to bytes
    img_bytes = result[1]
    # Convert to numpy array
    nparr = np.frombuffer(img_bytes, np.uint8)
    # Convert to image
    img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
    return img

# Test code
store_image('image.jpg')
img = retrieve_image(1)
cv2.imwrite('retrieved_image.jpg', img)