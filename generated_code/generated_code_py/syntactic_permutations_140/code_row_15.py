import mysql.connector
from mysql.connector import errorcode

try:
    connection = mysql.connector.connect(user='username', password='password', host='host', database='database')
    
    cursor = connection.cursor()
    query = "SELECT EXISTS(SELECT 1 FROM users WHERE username = %s) AS result"
    cursor.execute(query, ('test_username'))
    
    for i in cursor:
        if i[0] == 1:
            return True
        else:
            return False
except mysql.connector.Error as err:
    if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
        print("Invalid username or password")
    elif err.errno == errorcode.ER_BAD_DB_ERROR:
        print("Database does not exist")
    else:
        print(err)
finally:
    connection.close()