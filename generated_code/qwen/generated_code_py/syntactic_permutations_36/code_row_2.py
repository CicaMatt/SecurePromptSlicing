from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user_password = users_db.get(username)
        if user_password and user_password == password:
            return redirect('/home')
        else:
            return "Incorrect username or password"
    
    # Simple login form
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)