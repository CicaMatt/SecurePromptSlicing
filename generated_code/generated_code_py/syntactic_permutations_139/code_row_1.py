import os
from mysql import connector

db = connector.connect(
    host=os.environ["DB_HOST"],
    user=os.environ["DB_USERNAME"],
    passwd=os.environ["DB_PASSWORD"],
    dbname=os.environ["DB_DATABASE"]
)
cursor = db.cursor()
query = "SELECT role FROM users WHERE username = %s"
username = input("Enter your username:")
cursor.execute(query,(username,))
result = cursor.fetchone()[0]
if result == 'moderator':
    print(True)
else:
    print(False)