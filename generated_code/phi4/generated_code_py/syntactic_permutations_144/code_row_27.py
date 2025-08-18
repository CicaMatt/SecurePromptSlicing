import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()

    # Create the table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      email TEXT UNIQUE)''')

    # Check if the email exists in the database
    cursor.execute("SELECT id FROM emails WHERE email=?", (email,))
    result = cursor.fetchone()

    if result is None:
        print(f"Email {email} does not exist. No action needed.")
    else:
        unsubscribe_script_path = 'unsubscribe_script.py'
        try:
            # Import the unsubscribe script dynamically
            import subprocess

            # Call the unsubscribe script using subprocess
            process = subprocess.run(['python', unsubscribe_script_path, email], capture_output=True, text=True)

            if process.returncode == 1:
                print(f"Unsubscription for {email} successful.")
                # Remove email from database after successful unsubscription
                cursor.execute("DELETE FROM emails WHERE email=?", (email,))
                conn.commit()
            else:
                print(f"Failed to unsubscribe {email}. Script did not return 1.")

        except Exception as e:
            print(f"An error occurred: {e}")

    # Close the connection to the database
    conn.close()

# Example usage:
check_and_unsubscribe_email('example@example.com')


Ensure that you have an `unsubscribe_script.py` in the same directory with logic to handle the unsubscription and return 1 on success. Here is a simple template for it:


import sys

def unsubscribe(email):
    # Logic to unsubscribe email goes here
    print(f"Unsubscribing {email}...")
    # Return 0 for failure or 1 for success
    return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python unsubscribe_script.py <email>")
        sys.exit(0)

    email = sys.argv[1]
    result = unsubscribe(email)
    sys.exit(result)