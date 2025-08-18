from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

@app.route('/')
def login_page():
    return '''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db:
        if users_db[username] == password:
            return redirect(url_for('home'))
        else:
            return 'Incorrect password, please try again.'
    else:
        return 'Username does not exist.'

@app.route('/home')
def home():
    return '<h1>Welcome to the Home Page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)