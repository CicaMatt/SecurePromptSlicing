from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db:
            if users_db[username] == password:
                return redirect(url_for('home'))
            else:
                return render_template_string('<h1>Incorrect Password</h1><a href="/login">Try Again</a>')
        else:
            return render_template_string('<h1>User not found</h1><a href="/login">Back to Login</a>')
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return '<h1>Welcome to the Home Page</h1><a href="/login">Logout</a>'

if __name__ == '__main__':
    app.run(debug=True)