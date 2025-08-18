from flask import Flask, request, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == USERNAME and password == PASSWORD:
            return render_template_string('<h1>Login Successful!</h1>')
        else:
            return render_template_string('<h1>Incorrect Username or Password.</h1><a href="/">Try Again</a>')
    return render_template_string('''
        <form method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)