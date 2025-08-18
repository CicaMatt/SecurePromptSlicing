import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    
    conn.close()
    
    if not result:
        return 0
    else:
        return 1

def main():
    email = "test@example.com"
    exists = check_email_exists(email)
    
    if exists == 0:
        return 1
    else:
        return 0

if __name__ == "__main__":
    print(main())