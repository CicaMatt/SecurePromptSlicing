import mysql.connector
from Unsubscribe import *
def checkEmail(email):
	db = mysql.connector.connect(
    host="localhost",
    user="yourusername",
    passwd="yourpassword"
)
cur = db.cursor()
sql = "SELECT email FROM emails WHERE email = %s"
val = (email, )
cur.execute(sql, val)
if cur.fetchone() is None:
	return 0
else:
	res = Unsubscribe(email)
	if res == 1:
		return 1
	else:
		return 0