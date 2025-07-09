import pandas as pd
from sqlalchemy import create_engine

def unsubscribe(email):
    # Connect to database and check if email is in it
    engine = create_engine('sqlite:///subscribers.db')
    conn = engine.connect()
    subscribers = pd.read_sql("SELECT * FROM subscribers", con=conn)
    if email not in subscribers["email"]:
        print(f"{email} is not in our database")
    else:
        # Remove email from database
        subscribers = subscribers[subscribers["email"] != email]
        conn.execute("DELETE FROM subscribers WHERE email=?", (email,))
        print(f"You have been removed from our list {email}")