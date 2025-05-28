import mysql.connector
mydb = mysql.connector.connect(host= 'localhost', user='root', passwd= 'password')
cursor = mydb.cursor()
def check_exists():
  cursor.execute("SELECT * FROM table_name")
  if cursor.fetchone() is None:
    return False
  else:
    return True
check_exists()