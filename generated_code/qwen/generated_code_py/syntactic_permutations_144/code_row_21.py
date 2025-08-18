import sqlite3

def check_email_and_run_script(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if not user:
        return 0
    
    script_result = run_external_script()
    
    if script_result == 0:
        return 1
    else:
        return 0

def run_external_script():
    # Placeholder for running an external script
    # This should be replaced with actual script invocation logic
    import subprocess
    result = subprocess.run(['python', 'external_script.py'], capture_output=True)
    return int(result.stdout.decode().strip()) if result.returncode == 0 else 1

# Example usage:
# print(check_email_and_run_script('example@example.com'))