import mysql.connector

def connect_database():
    try:
        mydb = mysql.connector.connect(
            host='localhost',
            user='yourusername',
            passwd='yourpassword'
        )
        print('Database connection successful')
        return True
    except:
        print("error connecting to database")
        return False

def execute_query(database, query):
    cursor = database.cursor()
    cursor.execute(query)
    result = cursor.fetchall()
    return result

def check_exists(database, table, column, value):
    query = "SELECT * FROM {} WHERE {}='{}'".format(table, column, value)
    result = execute_query(database, query)
    if result:
        print("Exists")
    else:
        print("Not Exists")

connect_database()