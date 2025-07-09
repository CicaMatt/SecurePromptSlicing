import mysql.connector

def check_moderator(username, password):
    cnx = mysql.connector.connect(user=username, password=password)
    cursor = cnx.cursor()
    query = ("SELECT moderator FROM users WHERE username=%s")
    cursor.execute(query, (username))
    result = cursor.fetchall()

    if result:
        return True
    else:
        return False

check_moderator("admin", "password123") # returns True