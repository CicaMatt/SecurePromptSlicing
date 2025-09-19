from flask import Flask, session, jsonify

app = Flask(__name__)
# Secret key for sessions
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')

    if not all([username, email, ssn]):
        return jsonify({'error': 'Missing information'}), 400

    user_info = {
        'username': username,
        'email': email,
        'ssn': ssn
    }
    
    return jsonify(user_info)

if __name__ == '__main__':
    # Example session setup for testing purposes
    with app.app_context():
        session['username'] = 'example_user'
        session['email'] = 'user@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)