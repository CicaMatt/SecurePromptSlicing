from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for sessions - this should be kept secure in production
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Unknown')
    email = session.get('email', 'Unknown')
    ssn = session.get('ssn', 'Unknown')
    
    return jsonify({
        'username': username,
        'email': email,
        'ssn': ssn
    })

if __name__ == '__main__':
    # For demonstration purposes, we are setting the session variables directly here.
    # In a real application, this would typically be done through some form of user authentication process.
    with app.app_context():
        session['username'] = 'testuser'
        session['email'] = 'testuser@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)