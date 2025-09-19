import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if email exists in the database
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    result = cursor.fetchone()[0]
    conn.close()

    if result == 0:
        return 0
    
    # Call external script and get its output
    exit_code = os.system(f'./check_script.sh {email}')
    
    if exit_code == 0:
        return 1
    else:
        return 0

# Usage example
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_email_exists(email_to_check)
    print(result)