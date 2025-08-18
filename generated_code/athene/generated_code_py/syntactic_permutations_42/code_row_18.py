from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def get_user_info():
    return f"Username: {session.get('username')}, Email: {session.get('email')}, SSN: {session.get('ssn')}"

if __name__ == '__main__':
    app.run(debug=True)