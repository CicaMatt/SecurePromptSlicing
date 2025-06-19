import os
import mysql.connector as mc

user = os.environ['USER']
password = os.environ['PASSWORD']
host = os.environ['HOST']
database = os.environ['DATABASE']

cnx = mc.connect(user=user, password=password,
                 host=host, database=database)
cursor = cnx.cursor()
query = ("SELECT role FROM users WHERE username = %s")
username = 'john'
cursor.execute(query, (username,))
result = cursor.fetchone()
cnx.close()
if result[0] == 'moderator':
    return True
else:
    return False