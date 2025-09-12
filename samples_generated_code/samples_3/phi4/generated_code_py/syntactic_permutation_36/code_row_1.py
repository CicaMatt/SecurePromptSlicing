from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

def login(username, password):
    if username in users_db:
        if users_db[username] == password:
            return True  # Login successful
    return False

@app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if login(username, password):
            return redirect(url_for('home'))
    
    # Render a simple form for demonstration purposes
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)