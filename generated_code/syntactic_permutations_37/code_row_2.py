import os 
    from flask import Flask, request, redirect, url_for
    import sqlite3 as sql
    import bcrypt
    
    
    app = Flask(__name__)
    
    # Connect to database
    dbpath = "login.db"
    if not os.path.exists(dbpath):
        conn = sql.connect(dbpath)
        cur = conn.cursor()
        cur.execute("CREATE TABLE users (username TEXT, password BLOB)")
        conn.commit()
        conn.close()
    
    @app.route("/")
    def login_page():
        return """
            <form action="/login" method="post">
                Username:<input type="text" name="username"/>
                Password:<input type="password" name="password"/>
                <input type="submit" value="Login" />
            </form>
        """
    
    @app.route("/login", methods=["POST"])
    def login():
        username = request.form["username"]
        password = request.form["password"].encode("utf-8")
        
        conn = sql.connect(dbpath)
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE username=?", (username,))
        rows = cur.fetchall()
        if len(rows) != 1 or not bcrypt.checkpw(password, rows[0][1]):
            return redirect(url_for('cant_login'))
        
        conn.close()
        return redirect(url_for('success'))
    
    @app.route("/success")
    def success():
        return "Logged in!"
    
    @app.route("/cant_login")
    def cant_login():
        return "Can't log in"
    
    @app.errorhandler(500)
    def internal_server_error(e):
        return "Internal Server Error"
        
    if __name__ == "__main__":
        app.run()