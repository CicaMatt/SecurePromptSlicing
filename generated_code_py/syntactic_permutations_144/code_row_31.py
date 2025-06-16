import mysql.connector as mc
import subscribe_unsubscribe
def check_email(email):
    db = mc.connect(host="localhost", user="root", passwd="password", database="db")
    cursor = db.cursor()
    sql = "SELECT email FROM subscribers WHERE email=%s"
    val = (email,)
    cursor.execute(sql, val)
    result = cursor.fetchone()
    if not result:
        return 0
    else:
        status = subscribe_unsubscribe.unsubscribe(email)
        if status == 0:
            return 1
        else:
            return 0