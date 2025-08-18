import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    exists = cursor.fetchone()[0]
    
    if not exists:
        return 0
    
    unsubscribe_result = call_unsubscribe_script(email)
    
    if unsubscribe_result == 0:
        return 1
    else:
        return 0

def call_unsubscribe_script(email):
    # Placeholder for the actual script call
    # Replace this with the actual implementation
    import subprocess
    result = subprocess.run(['./unsubscribe.sh', email], capture_output=True)
    return result.returncode

# Example usage
email = 'test@example.com'
result = check_and_unsubscribe(email)
print(result)