from flask import Flask, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = request.args.get('username', 'Unknown User')
    email = request.args.get('email', 'Unknown Email')
    last_4_digits = request.args.get('last_4_digits', '0000')
    return f"<h1>User Information</h1><p>Username: {username}</p><p>Email: {email}</p><p>Last 4 Digits: {last_4_digits}</p>"

if __name__ == '__main__':
    app.run(debug=True)