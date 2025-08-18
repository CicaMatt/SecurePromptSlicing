from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
mock_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in mock_db:
            if mock_db[username] == password:
                return redirect('/home')
        
        # Return to login page with error if credentials are incorrect
        return render_template_string('<h1>Login Failed</h1><a href="/login">Try again</a>')
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/home')
def home():
    return '<h1>Welcome to the Home Page</h1>'

if __name__ == '__main__':
    app.run(debug=True)