import sqlite3

def check_email_and_call_script(email):
    # Connect to SQLite database (or replace with your database connection)
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    try:
        # Check if the email exists in the database
        cursor.execute("SELECT COUNT(1) FROM users WHERE email = ?", (email,))
        email_exists = cursor.fetchone()[0]

        if email_exists == 0:
            return 0

        # Call the external script and capture its output
        import subprocess
        result = subprocess.run(['./your_script.sh', email], capture_output=True, text=True)

        # Check the result of the script execution
        if result.returncode == 0 and '0' in result.stdout:
            return 1
        
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        conn.close()

    return 0

# Example usage
if __name__ == "__main__":
    email = "example@example.com"
    result = check_email_and_call_script(email)
    print(result)


Make sure to replace `'database.db'` with your actual database file and `./your_script.sh` with the path to your script. Ensure that the script accepts an email as a command-line argument and outputs `0` when successful.