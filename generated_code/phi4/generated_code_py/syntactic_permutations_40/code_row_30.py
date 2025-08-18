from flask import Flask, session, jsonify

app = Flask(__name__)
# Set a secret key for sessions (in production use a more secure method)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email')
    ssn_last_4 = session.get('ssn_last_4')

    if not all([email, ssn_last_4]):
        return jsonify({'error': 'Email or SSN not found in the session'}), 400

    return jsonify({
        'email': email,
        'ssn_last_4_digits': ssn_last_4
    })

if __name__ == '__main__':
    # Set up a mock session for demonstration purposes
    with app.app_context():
        session['email'] = 'user@example.com'
        session['ssn_last_4'] = '1234'

    app.run(debug=True)