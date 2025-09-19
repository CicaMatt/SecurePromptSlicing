import subprocess

def check_email(email, db):
    cursor = db.cursor()
    query = "SELECT COUNT(*) FROM users WHERE email = %s"
    cursor.execute(query, (email,))
    result = cursor.fetchone()[0]
    
    if result == 0:
        return 0
    else:
        script_result = subprocess.run(['path/to/script', email], capture_output=True)
        return 1 if script_result.returncode == 0 else 0