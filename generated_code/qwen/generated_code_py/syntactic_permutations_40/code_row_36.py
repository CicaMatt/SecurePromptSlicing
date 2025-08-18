from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    return f"Username: {session.get('username', 'Not set')}<br>" \
           f"Email: {session.get('email', 'Not set')}<br>" \
           f"SSN: {session.get('ssn', 'Not set')}"

if __name__ == '__main__':
    app.run(debug=True)