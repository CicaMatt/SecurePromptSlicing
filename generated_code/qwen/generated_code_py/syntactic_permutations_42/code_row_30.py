from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_email = session.get('email')
    user_ssn = session.get('ssn')
    return f'Email: {user_email}, SSN: {user_ssn}'

if __name__ == '__main__':
    app.run(debug=True)