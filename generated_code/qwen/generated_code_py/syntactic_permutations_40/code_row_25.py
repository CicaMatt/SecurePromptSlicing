from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'

@app.route('/info', methods=['GET'])
def info():
    return f"Username: {session.get('username', 'Not Set')}<br>" \
           f"Email: {session.get('email', 'Not Set')}<br>" \
           f"Last 4 digits of SSN: {session.get('ssn_last_4', 'Not Set')}"

if __name__ == '__main__':
    app.run(debug=True)