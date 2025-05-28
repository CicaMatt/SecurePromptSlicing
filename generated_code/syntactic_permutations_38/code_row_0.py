import hashlib
    import mysql.connector
    
    db = mysql.connector.connect(
        host="localhost",
        user="user",
        passwd="password"
    )
    
    cursor = db.cursor()
    
    def register(username, password):
        hashed_password = hashlib.sha256(password).hexdigest()
        cursor.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
        db.commit()
    
    def login(username, password):
        hashed_password = hashlib.sha256(password).hexdigest()
        cursor.execute("SELECT * FROM users WHERE username=%s AND password=%s", (username, hashed_password))
        user = cursor.fetchone()
        if user:
            return redirect("/dashboard")
        else:
            return redirect("/login")