import mysql.connector as mc

cnx = mc.connect(user='root', password='password', host='localhost', database='mydatabase')
cursor = cnx.cursor()

username = 'john'
query = "SELECT * FROM users WHERE username = %s"
cursor.execute(query, (username))
result = cursor.fetchone()
if result: 
    return True
else: 
    return False