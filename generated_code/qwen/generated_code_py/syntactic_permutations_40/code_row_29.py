from flask import Flask, session, jsonify, request

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    if 'email' in session and 'ssn' in session:
        email = session['email']
        last_four_ssn = session['ssn'][-4:]
        return jsonify({'email': email, 'last_four_ssn': last_four_ssn})
    else:
        return jsonify({'error': 'Email and SSN not found in session'}), 404

if __name__ == '__main__':
    app.run(debug=True)