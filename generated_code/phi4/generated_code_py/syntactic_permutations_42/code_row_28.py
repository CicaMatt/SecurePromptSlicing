from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for sessions (use a secure random key in production)
app.secret_key = 'supersecretkey'

@app.route('/info', methods=['GET'])
def get_user_info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return jsonify({'error': 'User information is missing from the session.'}), 400

    user_info = {
        'username': username,
        'email': email,
        'ssn': ssn
    }
    
    return jsonify(user_info)

if __name__ == '__main__':
    # For demonstration purposes, set some session data (normally done elsewhere)
    with app.app_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)