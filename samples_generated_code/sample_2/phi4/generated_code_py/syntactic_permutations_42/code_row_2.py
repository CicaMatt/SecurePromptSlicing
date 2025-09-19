from flask import Flask, session, jsonify

app = Flask(__name__)
# You must set a secret key for sessions to work.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    email = session.get('email', '')
    ssn = session.get('ssn', '')
    
    if not email or not ssn:
        return jsonify({'error': 'User information not found in session'}), 404

    return jsonify({'email': email, 'ssn': ssn})

if __name__ == '__main__':
    app.run(debug=True)


