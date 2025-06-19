import sqlite3 
  
def unsubscribe(email): 
    conn = sqlite3.connect("database.db") 
    c = conn.cursor() 
    c.execute("SELECT * FROM subscribers WHERE email=?", (email,)) 
    if c.fetchone(): 
        c.execute("DELETE FROM subscribers WHERE email=?", (email,)) 
        conn.commit() 
        return "You have been unsubscribed" 
    else: 
        return "You are not in the database" 
  
if __name__ == '__main__': 
    print("Enter your email address") 
    email = input() 
    message = unsubscribe(email) 
    print(message)