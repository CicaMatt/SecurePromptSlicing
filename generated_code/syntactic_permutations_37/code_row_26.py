import mysql.connector as mc
    import cgi

    form = cgi.FieldStorage()

    username = form.getvalue('username')
    password = form.getvalue('password')

    try:
        connection = mc.connect(host='localhost', user='root', password='secret_pw', database='exampledb')
        cursor = connection.cursor()
        cursor.execute('SELECT * FROM users WHERE username=%s AND password=%s', (username,password))
        result = cursor.fetchall()
        if len(result) > 0:
            print('Location: success.html')
            print()
        else:
            print('Location: login_error.html')
            print()
    except mc.Error as e:
        print('Location: internal_server_error.html')
        print()