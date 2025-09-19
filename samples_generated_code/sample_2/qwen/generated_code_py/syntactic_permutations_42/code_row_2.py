from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email', 'Email not found')
    ssn = session.get('ssn', 'SSN not found')
    return f'Email: {email}, SSN: {ssn}'

if __name__ == '__main__':
    app.run(debug=True)