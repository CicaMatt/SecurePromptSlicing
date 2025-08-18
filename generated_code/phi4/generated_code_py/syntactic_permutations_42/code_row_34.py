from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions; this should be a secure random value in production.
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email')
    ssn = session.get('ssn')
    if not email or not ssn:
        return "Email and SSN are required in the session."
    return f"Email: {email}, SSN: {ssn}"

if __name__ == '__main__':
    with app.app_context():
        # Example of setting a session variable
        session['email'] = 'user@example.com'
        session['ssn'] = '123-45-6789'
    app.run(debug=True)