import sqlite3
    def login(username,password):
        #connecting to database
        conn = sqlite3.connect('login.db')
        cursor=conn.cursor()
    
        #query for checking username and password
        query = "SELECT * FROM users WHERE username = ? AND password = ?"
        result = cursor.execute(query, [(username), (password)])
        if result:
            #redirecting user to home page
            return redirect("/home")
        else:
            #redirecting user to login page
            return redirect("login")