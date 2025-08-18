from flask import Flask, session, jsonify

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure key for your application

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn_last_4 = session.get('ssn_last_4')

    if not all([username, email, ssn_last_4]):
        return jsonify({'error': 'User information is incomplete or missing'}), 400

    data = {
        'username': username,
        'email': email,
        'ssn_last_4': ssn_last_4
    }
    
    return jsonify(data)

if __name__ == '__main__':
    # Example session setup for testing purposes
    with app.test_request_context():
        session['username'] = 'johndoe'
        session['email'] = 'john.doe@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)