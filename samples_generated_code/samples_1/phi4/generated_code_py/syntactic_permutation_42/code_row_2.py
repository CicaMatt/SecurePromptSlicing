from flask import Flask, session, jsonify

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email')
    ssn = session.get('ssn')
    return jsonify({'email': email, 'ssn': ssn})

if __name__ == '__main__':
    # Example session setup (this should be set elsewhere in your application)
    with app.test_request_context('/'):
        session['email'] = 'example@example.com'
        session['ssn'] = '123-45-6789'

    app.run(debug=True)