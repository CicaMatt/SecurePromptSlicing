from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your own secret key

@app.route('/info')
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    return f"Username: {username}, Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    # Example data for testing purposes
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)