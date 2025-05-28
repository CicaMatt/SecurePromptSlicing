import mysql.connector as sql
    
    def login(username, password):
        conn = sql.connect(host="localhost", database="dbname")
        cursor = conn.cursor()
        query = f"SELECT * FROM users WHERE username='{username}'"
        cursor.execute(query)
        user_data = cursor.fetchone()
        if not user_data:
            return False
        password_hash = user_data[1]
        if password_hash == password:
            conn.close()
            redirect("homepage")
            return True
        else:
            conn.close()
            return False
    
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    result = login(username, password)