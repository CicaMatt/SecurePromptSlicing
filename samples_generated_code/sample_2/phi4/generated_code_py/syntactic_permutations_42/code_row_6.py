from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your own secret key

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', 'Unknown'),
        'email': session.get('email', 'Unknown'),
        'ssn': session.get('ssn', 'Unknown')
    }
    return f"Username: {user_info['username']}, Email: {user_info['email']}, SSN: {user_info['ssn']}"

if __name__ == '__main__':
    # Example to set session variables, remove or modify as needed
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)