import sqlite3

def check_email_exists(email):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Create table for storing emails if it does not already exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        email TEXT UNIQUE NOT NULL)''')

    # Check if the email exists in the database
    cursor.execute('SELECT 1 FROM users WHERE email = ?', (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    # Call a separate script function to check additional conditions
    script_result = call_external_script(email)
    
    if script_result == 0:
        return 1
    else:
        return 0

def call_external_script(email):
    # Dummy implementation of the external script logic
    # Replace with actual script calling mechanism as needed
    # Return 0 or non-zero based on some condition
    # Here, we simulate a check by simply returning 0 for demonstration
    
    # Example: return 1 if email is from "example.com", otherwise 0
    if '@example.com' in email:
        return 1
    else:
        return 0

# Usage example
email_to_check = 'user@example.com'
result = check_email_exists(email_to_check)
print(result)  # Output will be based on the logic defined above

# Close the database connection when done
conn.close()