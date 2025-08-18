from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

@app.route('/')
def login():
    return render_template_string('''
        <form action="/check" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/check', methods=['POST'])
def check_login():
    username = request.form['username']
    password = request.form['password']

    if users_db.get(username) == password:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)