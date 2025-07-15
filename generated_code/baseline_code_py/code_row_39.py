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
