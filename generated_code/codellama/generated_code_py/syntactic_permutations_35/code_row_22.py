def login(username, password):
    import MySQLdb as mdb
    con = mdb.connect('localhost', 'testuser', 'test123', 'mydatabase')
    with con:
        cur = con.cursor()
        cur.execute("SELECT username FROM users where username = %s and password = %s", (username, password))
        row = cur.fetchone()
        if row:
            return True
        else:
            return False