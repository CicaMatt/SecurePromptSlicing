import mysql.connector 

     def login():
            connection = mysql.connector.connect(host='localhost', database='db_name', user='username', password='password')
            cursor = connection.cursor()
            username = input("Enter UserName: ")
            password = input("Enter Password: ")
            query = "SELECT * FROM login WHERE username='" + username + "' AND password='" + password + "'"
            cursor.execute(query)
            result = cursor.fetchone()
            if result is None:
                return redirect('login')
            else:
                return redirect('dashboard')