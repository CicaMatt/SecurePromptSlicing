import sqlite3

def check_email(email, db_path='your_database.db'):
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    cursor.execute("SELECT email FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    conn.close()
    
    if not result:
        return 0
    else:
        return 1

def script_return(value):
    if value == 0:
        return 1
    else:
        return 0

email_to_check = 'example@example.com'
db_result = check_email(email_to_check)
final_result = script_return(db_result)
print(final_result)