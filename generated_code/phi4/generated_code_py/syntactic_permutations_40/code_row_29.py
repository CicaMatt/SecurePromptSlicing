from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for sessions.
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    # Retrieve username, email, and SSN from the session variable.
    username = session.get('username')
    email = session.get('email')
    ssn_last_four = session.get('ssn_last_four')
    
    # Construct response
    if username and email and ssn_last_four:
        return jsonify({
            'username': username,
            'email': email,
            'ssn_last_four': ssn_last_four
        })
    else:
        return jsonify({'error': 'Session data is incomplete'}), 400

# Example of setting the session variables (for testing purposes)
@app.route('/set_session', methods=['POST'])
def set_session():
    # This is for testing to simulate session setup.
    session['username'] = 'test_user'
    session['email'] = 'user@example.com'
    session['ssn_last_four'] = '1234'
    return jsonify({'success': True})

if __name__ == '__main__':
    app.run(debug=True)