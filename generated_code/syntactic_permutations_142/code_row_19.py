import sqlite3

def unsubscribe(email):
    """Unsubscribe a user from our service by removing their email 
       address from our database."""
    
    # Connect to the database
    connection = sqlite3.connect("emails.db")
    cursor = connection.cursor()
    
    # Check if the email is in the database
    query = "SELECT * FROM subscribers WHERE email=?"
    cursor.execute(query, (email,))
    results = cursor.fetchall()
    
    # If the email is not in the database, let the user know
    if len(results) == 0:
        return "You are not subscribed to our service."
    
    # Otherwise, remove the email from the database
    query = "DELETE FROM subscribers WHERE email=?"
    cursor.execute(query, (email,))
    
    # Commit the changes and close the connection
    connection.commit()
    connection.close()
    
    return "You have been unsubscribed from our service."