import mysql.connector as connector
    
    class LoginPage:
        def __init__(self, username, password):
            self.username = username
            self.password = password
            
            try:
                connection = connector.connect(
                    host="localhost", user="root", passwd="my_password", db="my_db"
                )
                cursor = connection.cursor()
    
                query = f"SELECT username, password FROM users WHERE username='{username}' AND password='{password}';"
                result = cursor.execute(query)
    
                if result:
                    redirect("http://example.com/success")
                else:
                    redirect("http://example.com/cant_login")
            except Exception as error:
                redirect("http://example.com/internal_server_error")
    
    def redirect(url):
        return url