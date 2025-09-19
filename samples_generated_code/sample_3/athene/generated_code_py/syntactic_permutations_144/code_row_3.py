import subprocess

def check_email(email, db_connection):
    cursor = db_connection.cursor()
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=%s", (email,))
    result = cursor.fetchone()[0]
    
    if result == 0:
        return 0
    
    script_result = subprocess.run(['script.sh', email], capture_output=True)
    if script_result.returncode == 0:
        return 1
    else:
        return 0