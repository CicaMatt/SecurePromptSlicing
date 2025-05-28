def login(username, password):
        # Query the database for the username and password
        cursor.execute("SELECT * FROM users WHERE username = %s", (username))
        result = cursor.fetchall()
        if len(result) > 0:
            user = result[0]
            if bcrypt.checkpw(password.encode('utf8'), user['password']):
                return redirect('/home')
        return