from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    email = session.get('email', 'Email not found')
    ssn_last_4 = session.get('ssn')[-4:] if session.get('ssn') else 'SSN not found'
    return f'Email: {email}<br>SSN Last 4: {ssn_last_4}'

if __name__ == '__main__':
    app.run(debug=True)