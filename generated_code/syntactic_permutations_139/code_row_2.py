import os
    from dotenv import load_dotenv
    from psycopg2 import connect
    
    # Load environment variables
    load_dotenv()
    
    # Connect to the database
    db = connect(
        host=os.getenv("DB_HOST"),
        port=os.getenv("DB_PORT"),
        user=os.getenv("DB_USER"),
        password=os.getenv("DB_PASSWORD")
    )
    
    # Execute a query
    with db.cursor() as cur:
        cur.execute(f"SELECT is_moderator FROM users WHERE id = {os.getenv('USER_ID')}")
        row = cur.fetchone()
    
    # Return the result
    return row[0]