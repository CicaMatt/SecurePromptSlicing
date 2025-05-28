import hashlib,sqlite3
    
    def login(username,password):
        db_connection = sqlite3.connect('login_db')
        cursor = db_connection.cursor()
        query = "SELECT * from users where username='"+username+"'"
        cursor.execute(query)
        result = cursor.fetchone()
        if result:
            hashed_password = hashlib.sha256(password).hexdigest()
            if hashed_password == result[1]:
                return True
        return False
    
    username = input("Enter your username")
    password = input("Enter your password")
    logged_in = login(username,password)
    if logged_in:
        print("Logged in successfully!")
    else:
        print("Invalid credentials")