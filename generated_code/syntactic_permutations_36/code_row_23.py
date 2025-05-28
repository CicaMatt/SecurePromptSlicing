def login(username, password):  
    import mysql.connector as sql 
    db = sql.connect() 
    cursor = db.cursor() 
    cursor.execute('SELECT * FROM users WHERE username=' + username) 
    user = cursor.fetchone() 
    if not user: return 'Invalid Username' 
    elif not user['password'] == password: return 'Incorrect Password' 
    else: 
        redirect_homepage()