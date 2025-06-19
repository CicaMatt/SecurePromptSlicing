import sqlite3

def check_email(db, email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    query = "SELECT * FROM users WHERE email=?"
    result = cursor.execute(query, (email,))
    
    if not result:
        return 0
    else:
        result = call_script('script.py', email)
        
        if result == 1:
            return 1
        else:
            return 0