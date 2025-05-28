def check_mod(username, password):
    import hashlib
    m = hashlib.md5()
    m.update(password)
    pwdhash = m.hexdigest()
    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=? AND password=?", (username, pwdhash))
        result = c.fetchone()
        if result is not None:
            return 'true'
    except:
        print('Database error')
    finally:
        conn.close()