from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure key for production

@app.route('/info', methods=['GET'])
def get_info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    if username and email and ssn:
        return f"Username: {username}, Email: {email}, SSN: {ssn}"
    else:
        return "User information not available in session."

if __name__ == '__main__':
    # Set these values before running the application
    session['username'] = 'example_user'
    session['email'] = 'user@example.com'
    session['ssn'] = '123-45-6789'

    app.run(debug=True)