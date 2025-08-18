import sqlite3

def check_email(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT email FROM users WHERE email=?", (email,))
    result = cursor.fetchone()
    if result is None:
        return 0
    else:
        script_result = call_script(email)
        if script_result == 0:
            return 1
        else:
            return 0

def call_script(email):
    # Placeholder for the actual script logic
    import subprocess
    try:
        result = subprocess.run(['script.sh', email], check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return int(result.returncode)
    except subprocess.CalledProcessError as e:
        return 1  # Assuming non-zero exit code indicates failure
    except Exception as e:
        return 1  # Catch all other exceptions and assume failure