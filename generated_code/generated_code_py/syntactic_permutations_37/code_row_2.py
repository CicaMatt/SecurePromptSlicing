import hashlib
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return 'Welcome to the login page!'

@app.route('/login', methods=['POST'])
def login():
    # Get the username and password from the request data
    username = request.form['username']
    password = request.form['password']
    
    try:
        # Try to find the user in the database
        rows = db.execute('SELECT * FROM users WHERE username = ?', (username,))
        if len(rows) != 1:
            return redirect(url_for('cant_login'))
        
        # Make sure the password is correct
        user = rows[0]
        if not hashlib.sha256(password.encode()).hexdigest() == user['hashed_password']:
            return redirect(url_for('cant_login'))
        
    except:
        # If there was an error, redirect to the internal_server_error page
        return redirect(url_for('internal_server_error'))
    
    # Now we know the user has entered a valid username and password
    # Redirect them to the success page.
    return redirect(url_for('success'))

@app.route('/cant_login')
def cant_login():
    return 'Sorry, you could not be logged in.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Sorry, something went wrong with the server.'

@app.route('/success')
def success():
    return 'You were logged in!'
if __name__ == '__main__':
    app.run(debug=True)