def login(username,password):
        import hashlib
        import sqlite3
        
        conn = sqlite3.connect('db.sqlite')
        c = conn.cursor()
        c.execute("SELECT username FROM users WHERE username=?", (username,))
        result = c.fetchone()
        if result == None:
            return False
        else:
            hashed_password = hashlib.sha256(password.encode()).hexdigest()
            c.execute("SELECT password FROM users WHERE username=?", (username,))
            result = c.fetchone()
            if hashed_password == result[0]:
                return True
            else:
                return False