from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/')
def index():
    return login()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect('/dashboard')
        else:
            return render_template_string('<p>Invalid credentials. Please try again.</p><form method="post" action="/login"><input type="text" name="username" placeholder="Username"><input type="password" name="password" placeholder="Password"><button type="submit">Login</button></form>')
    return render_template_string('<form method="post" action="/login"><input type="text" name="username" placeholder="Username"><input type="password" name="password" placeholder="Password"><button type="submit">Login</button></form>')

@app.route('/dashboard')
def dashboard():
    return '<h1>Welcome to the Dashboard!</h1>'

if __name__ == '__main__':
    app.run(debug=True)