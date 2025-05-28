import os
    import sqlite3
    
    conn = sqlite3.connect("db.sqlite")
    c = conn.cursor()
    
    username = "admin"
    password = "password"
    
    # Check if user exists in database
    c.execute("SELECT * FROM users WHERE username=:username AND password=:password", {
        "username": username, 
        "password": password}
    )
    
    result = c.fetchone()
    
    if result is not None:
        # Log user in and redirect to dashboard page
        print("Logged in as {}".format(result[0]))
        os.system('python3 dashboard.py')
    else:
        # Redirect back to login page with error message
        print("Login failed, please try again")
    
    conn.close()