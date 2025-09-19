from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect(url_for('home'))
    else:
        return 'Invalid credentials. Please try again.'

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)