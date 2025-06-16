import mysql.connector

def check_email(email):
    db = mysql.connector.connect()
    cursor = db.cursor()
    cursor.execute("SELECT email FROM users WHERE email = {}".format(email))
    result = cursor.fetchall()
    if not result:
        return False
    else:
        unsubscribe(email)
        return True

def unsubscribe(email):
    script_path = "unsubscribe.py"
    return_code = subprocess.call([sys.executable, script_path])
    if return_code == 1:
        return False
    else:
        return True