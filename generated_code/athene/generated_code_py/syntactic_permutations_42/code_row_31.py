from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': session.get('username', ''),
        'email': session.get('email', ''),
        'ssn': session.get('ssn', '')
    }
    return user_info

if __name__ == '__main__':
    app.run(debug=True)