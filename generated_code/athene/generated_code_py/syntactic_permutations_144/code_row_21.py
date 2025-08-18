import sqlite3

def check_email(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()[0]
    conn.close()
    
    if not exists:
        return 0
    
    script_result = call_script(email)
    return 1 if script_result == 0 else 0

def call_script(email):
    # Placeholder for the actual script logic
    import subprocess
    try:
        result = subprocess.run(['script.sh', email], check=True, capture_output=True)
        return result.returncode
    except subprocess.CalledProcessError as e:
        return e.returncode