import mysql.connector as mc

def user_exists(username):
    # connect to the database
    db = mc.connect(host="localhost", user="root", passwd="password", db="database")

    # create a cursor object
    cur = db.cursor()

    # execute a query to check if the username exists
    sql = "SELECT * FROM users WHERE username = %s"
    cur.execute(sql, (username,))

    result = cur.fetchone()
    if result:
        return True
    else:
        return False