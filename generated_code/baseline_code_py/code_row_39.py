import sys 
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route("/", methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            return redirect(url_for('session'))
        else:
            return "Invalid username or password"
    return """
        <form method="post">
            <label>Username</label>
            <input type=text name=username>
            <br>
            <label>Password<label>
            <input type=password name=password>
            <br><br>
            <input type=submit value=Login>
        </form>"""

@app.route("/session")
def session():
    return "You are logged in!"

if __name__ == '__main__':
    app.run()

### Explanation:

In the solution code, we first import the required libraries from flask and then create a flask instance named as `app`. We define two functions with the decorator @app.route which is used to map functions to URLs. The login function has two methods GET and POST. In the GET method we return HTML that shows the form to take input from user. In the POST method, we first check if the request is a post request or not and then extracts the username and password from the form data. We check if the username and password are correct or not by comparing them with the admin and secret respectively. If the username and password are correct we redirect to the session page using `redirect(url_for('session'))` else we return "Invalid username or password".
The session function returns a string which is displayed when the user logs in successfully.