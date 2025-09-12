from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if check_credentials(username, password):
            return redirect('/home')
    
    # Simple HTML form for demonstration
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

def check_credentials(username, password):
    if username in users_db:
        return users_db[username] == password
    return False

if __name__ == '__main__':
    app.run(debug=True)