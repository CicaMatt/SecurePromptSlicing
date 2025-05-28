import mysql.connector

mydb = mysql.connector.connect(
    host="localhost",
    user="yourusername",
    passwd="yourpassword"
)

mycursor = mydb.cursor()

def check_username(username):
    mycursor.execute("SELECT * FROM users WHERE username = " + username)
    myresult = mycursor.fetchall()
    if myresult:
        return True
    else:
        return False