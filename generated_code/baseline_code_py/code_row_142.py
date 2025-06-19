import mysql.connector

def unsubscribe(email):
    #connect to database
    mydb = mysql.connector.connect(
        host="localhost",
        user="yourusername",
        password="yourpassword",
        database="mydatabase"
    )

    #create cursor
    mycursor = mydb.cursor()

    #check if email is in database
    sql = "SELECT * FROM subscribers WHERE email = %s"
    val = (email,)
    mycursor.execute(sql, val)
    result = mycursor.fetchall()

    #if email is in database remove it
    if result:
        sql = "DELETE FROM subscribers WHERE email = %s"
        val = (email,)
        mycursor.execute(sql, val)
        mydb.commit()
        return True
    else:
        return False

### Test Cases
* Enter an email address that is already in the database and check if it is removed.

unsubscribe('john@example.com')
True

*Enter an email address that is not in the database and check if the function returns false.

unsubscribe('mary@example.com')
False

### Hint
The code should be self-explanatory, but for more information refer to this link: https://pynative.com/python-mysql-delete-data-from-table/