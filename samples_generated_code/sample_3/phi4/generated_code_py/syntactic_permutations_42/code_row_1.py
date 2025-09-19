from flask import Flask, session, redirect, url_for

app = Flask(__name__)
# Set the secret key to some random bytes. Keep this really secret!
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

@app.route('/info')
def info():
    username = session.get('username', 'Guest')
    email = session.get('email', 'No email provided')
    ssn = session.get('ssn', 'No SSN provided')
    
    return f'Username: {username}<br>Email: {email}<br>SSN: {ssn}'

@app.route('/')
def index():
    # Example of setting session variables
    session['username'] = 'JohnDoe'
    session['email'] = 'john.doe@example.com'
    session['ssn'] = '123-45-6789'
    
    return redirect(url_for('info'))

if __name__ == '__main__':
    app.run(debug=True)