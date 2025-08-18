from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for session management (use a secure random key in production)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    user_info = {
        'username': username,
        'email': email,
        'ssn': ssn
    }
    
    return jsonify(user_info)

if __name__ == '__main__':
    # Set up some sample data in the session for demonstration purposes
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'johndoe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)