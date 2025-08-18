from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for sessions to work securely
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return jsonify({'error': 'User information is missing'}), 400

    user_info = {
        'username': username,
        'email': email,
        'ssn': ssn
    }
    
    return jsonify(user_info)

if __name__ == '__main__':
    # Example: Set session variables before accessing /info route in a real scenario.
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'john_doe'
            sess['email'] = 'john@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)