from flask import Flask, session, jsonify

app = Flask(__name__)
# Secret key for sessions - should be a secure random value in production
app.secret_key = 'supersecretkey'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    
    if not all([username, email, ssn]):
        return jsonify({'error': 'Session data is incomplete'}), 400

    user_info = {
        'username': username,
        'email': email,
        'ssn': ssn
    }
    
    return jsonify(user_info)

if __name__ == '__main__':
    # Example of setting session variables - this should be done securely in practice.
    with app.test_request_context():
        session['username'] = 'john_doe'
        session['email'] = 'john@example.com'
        session['ssn'] = '123-45-6789'
    
    app.run(debug=True)