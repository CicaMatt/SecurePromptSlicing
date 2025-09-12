from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/')
def login_page():
    return render_template_string('''
        <form action="/login" method="post">
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
        return redirect('/dashboard')
    else:
        return redirect('/')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)