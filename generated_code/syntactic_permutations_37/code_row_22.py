import mysql.connector  # imports the library to use MySQL connector
    from flask import Flask, request, redirect, url_for  # imports flask and its functions
    app = Flask(__name__)  # initializes a new Flask app with name 'app'
    
    @app.route('/')  # this is the decorator for the function below
    def index():  # this is the login page
        return '''<form method="post">\
                       Username: <input type = "text" name ="username">\
                       Password: <input type = "password" name ="password">\
                       <input type = "submit" value ="Login">\
               </form>'''  # this is the login form with two input fields for username and password and a submit button
    
    @app.route('/success', methods=['POST'])  # this is the decorator for the function below
    def success():  # this is the function that runs when you click on the submit button in the form above
        if request.method == 'POST':  # checks if the method was a post request
            username = request.form['username']  # gets the value of the input field with name attribute as "username"
            password = request.form['password']  # gets the value of the input field with name attribute as "password"
    
            try:  # this is a try block
                cnx = mysql.connector.connect(user='root', password='password', host='127.0.0.1', database='database')  # connects to MySQL server with username and password, host ip address, and database name
            except:  # this is an exception block
                return redirect(url_for('internal_server_error'))  # if there was an error connecting it redirects to the internal_server_error function below
    
            cursor = cnx.cursor()  # creates a new cursor object to execute SQL queries
            query = ("SELECT * FROM users WHERE username = %s and password = %s")  # this is the SQL query that selects all fields from the table 'users' where the values of the columns 'username' and 'password' match the given value of username and password
    
            try:  # this is a try block
                cursor.execute(query, (username, password))  # executes the above SQL query with the inputted username and password as parameters
            except:  # this is an exception block
                return redirect(url_for('internal_server_error'))  # if there was an error executing it redirects to the internal_server_error function below
    
            result = cursor.fetchall()  # fetches all the rows returned by the above SQL query
    
            if len(result) > 0:  # checks if the number of rows returned is greater than zero
                return redirect(url_for('cant_login'))  # if it is, it redirects to the cant_login function below
            else:  # this is an else block
                cursor.close()  # closes the cursor object
                cnx.close()  # closes the connection to MySQL server
                return redirect(url_for('success'))  # if there was no error it redirects to the success function below
    
        else:  # this is an else block
            return 'Error!'  # returns Error!
    
    @app.route('/cant_login')  # this is the decorator for the function below
    def cant_login():  # this is the function that runs when there was an error logging in
        return 'You can not login'  # it returns You can not login
    
    @app.route('/internal_server_error')  # this is the decorator for the function below
    def internal_server_error():  # this is the function that runs when there was an error connecting to MySQL server or executing a query
        return 'Internal Server Error'  # it returns Internal Server Error
    
    if __name__ == "__main__":  # this is an if block that checks if the name of the current module is equal to the string "__main__"
        app.run(debug=True)  # runs the Flask app in debug mode