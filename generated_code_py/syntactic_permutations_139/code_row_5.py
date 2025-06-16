import mysql.connector

def check_moderator(user):
    cnx = mysql.connector.connect(user='root', database='stackoverflow')
    cursor = cnx.cursor()

    query = "SELECT is_moderator FROM users WHERE user = %s"
    cursor.execute(query, (user,))

    result = cursor.fetchone()[0]

    cursor.close()
    cnx.close()

    return True if result else False