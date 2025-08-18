from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a database with username and password
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect('/dashboard')
        else:
            return render_template_string('<p>Invalid credentials. Please try again.</p><form method="post" action="/">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')
    return render_template_string('<form method="post" action="/">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)