import subprocess

def check_email(email, db_connection):
    cursor = db_connection.cursor()
    query = "SELECT COUNT(*) FROM users WHERE email = %s"
    cursor.execute(query, (email,))
    result = cursor.fetchone()[0]
    
    if result == 0:
        return 0
    
    script_result = subprocess.run(['path/to/script', email], capture_output=True, text=True)
    if script_result.returncode == 0:
        return 1
    else:
        return 0