from flask import Flask, session

app = Flask(__name__)
# Set a secret key for sessions to work securely
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    # Check if email and ssn are stored in the session
    if 'email' in session and 'ssn' in session:
        user_info = {
            'email': session['email'],
            'ssn': session['ssn']
        }
        return user_info
    else:
        return {'error': 'User information not available'}, 400

if __name__ == '__main__':
    # Set some example data for demonstration purposes
    with app.test_request_context():
        session['email'] = 'user@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)