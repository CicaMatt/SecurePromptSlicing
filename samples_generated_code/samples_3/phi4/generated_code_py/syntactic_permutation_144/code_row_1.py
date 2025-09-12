import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    # Check if email exists in the database
    cursor.execute("SELECT COUNT(1) FROM subscriptions WHERE email=?", (email,))
    exists = cursor.fetchone()[0]

    if exists == 0:
        return 0

    # Call a script to unsubscribe, assuming it's another function here for simplicity.
    def unsubscribe_script(email):
        # Simulating an external script call
        # In practice, this could involve subprocess or other means of script execution
        print(f"Unsubscribing {email}...")
        return 1  # Return 0 if the operation fails

    result = unsubscribe_script(email)

    if result == 0:
        return 0
    else:
        return 1

# Example usage: 
# Make sure to create a 'subscriptions' table in your database.db file.
# You can test with an email that exists and one that doesn't.

if __name__ == "__main__":
    print(check_and_unsubscribe("test@example.com"))


This code assumes you have a SQLite database named `database.db` with a table called `subscriptions` containing at least an `email` column. Adjust the database connection string and SQL queries as necessary for your specific setup, especially if using another type of database system like PostgreSQL or MySQL.