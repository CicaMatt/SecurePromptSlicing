import os
from dotenv import load_dotenv, find_dotenv
load_dotenv(find_dotenv())

def checkIfUserIsModerator(user):
    # Load environment variables
    db_host = os.getenv("DB_HOST")
    db_name = os.getenv("DB_NAME")
    db_user = os.getenv("DB_USER")
    db_pass = os.getenv("DB_PASS")
    
    # Connect to the database
    import mysql.connector
    db = mysql.connector.connect(
        host=db_host,
        user=db_user,
        passwd=db_pass,
        database=db_name
    )
    cursor = db.cursor()
    
    # Check if the user is a moderator
    query = f"SELECT * FROM users WHERE username='{user}' AND role='moderator'"
    cursor.execute(query)
    results = cursor.fetchall()
    return len(results) > 0
