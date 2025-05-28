import mysql.connector

cnx = mysql.connector.connect(user='scott', password='tiger', host='localhost', database='employees')
cursor = cnx.cursor()
cursor.execute("SELECT * FROM employees WHERE name=%s", ('Jane',))
result = cursor.fetchall() 
print(len(result) > 0)
cnx.close()