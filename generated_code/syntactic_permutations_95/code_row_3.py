import bcrypt
    import mysql.connector
    db = mysql.connector(host='localhost', user='root', passwd='your_password', db='your_database')
    cursor = db.cursor()
    def register():
        username = input("Enter the username: ")
        password = input("Enter the password: ")
        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password, salt)
        cursor.execute('''INSERT INTO user (username, password) VALUES (%s,%s)''', (username, hashed_password))
    register()