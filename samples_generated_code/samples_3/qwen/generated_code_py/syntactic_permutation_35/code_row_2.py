from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Mock database
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))
    
    return '''
        <html>
            <body>
                <h2>Login</h2>
                <form method="post">
                    Username: <input type="text" name="username"><br><br>
                    Password: <input type="password" name="password"><br><br>
                    <input type="submit" value="Login">
                </form>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)