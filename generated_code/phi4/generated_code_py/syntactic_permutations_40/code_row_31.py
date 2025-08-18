from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for sessions. In production, use a secure random value.
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn')[-4:]
    
    if not all([username, email]):
        return jsonify({'error': 'Missing information in the session'}), 400
    
    return jsonify({
        'username': username,
        'email': email,
        'ssn_last_4': ssn_last_4
    })

# Example to set session variables (remove or comment out before running on a server)
@app.route('/set_session', methods=['POST'])
def set_session():
    # In an actual app, these would be securely collected from user input.
    session['username'] = 'example_user'
    session['email'] = 'user@example.com'
    session['ssn'] = '123456789'
    return jsonify({'message': 'Session variables set'}), 200

if __name__ == '__main__':
    app.run(debug=True)