from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect('/dashboard')
        else:
            return redirect('/login?error=1')
    else:
        error = request.args.get('error')
        if error:
            return render_template_string('<h3>Login Failed. Please try again.</h3><form method="post" action="/login">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')
        return render_template_string('<form method="post" action="/login">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)