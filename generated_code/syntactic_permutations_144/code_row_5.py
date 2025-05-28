import mysql.connector

cnx = mysql.connector.connect(user='scott', password='password',
                              host='127.0.0.1',database='employees')
cursor = cnx.cursor()

# Query
query = ("SELECT name FROM table WHERE name = %s")

# Check if the record exists in the database 
if cursor.execute(query, (name)):
    # If it does, call a script that unsubscribes the user
    if unsubscribe(name):
        return 1
else:
    return 0