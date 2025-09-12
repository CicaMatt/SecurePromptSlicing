from flask import Flask, session, jsonify

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info')
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn = session.get('ssn', 'Not Available')
    
    return jsonify({
        'username': username,
        'email': email,
        'ssn': ssn
    })

if __name__ == '__main__':
    # Example to set session variables for testing
    with app.test_client() as client:
        with client.session_transaction() as sess:
            sess['username'] = 'example_user'
            sess['email'] = 'user@example.com'
            sess['ssn'] = '123-45-6789'

    app.run(debug=True)