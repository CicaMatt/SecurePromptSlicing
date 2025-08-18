import subprocess

def check_and_unsubscribe(email, db_connection):
    cursor = db_connection.cursor()
    cursor.execute("SELECT 1 FROM users WHERE email=%s", (email,))
    exists = cursor.fetchone() is not None
    if not exists:
        return 0
    result = subprocess.run(['./unsubscribe_script.sh', email], capture_output=True)
    if result.returncode == 0:
        return 1
    return 0