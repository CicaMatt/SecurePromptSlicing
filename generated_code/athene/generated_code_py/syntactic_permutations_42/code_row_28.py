from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def get_user_info():
    user_info = f"Username: {session.get('username', 'Not set')}, Email: {session.get('email', 'Not set')}, SSN: {session.get('ssn', 'Not set')}"
    return user_info

if __name__ == '__main__':
    app.run(debug=True)