from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    user_data = {
        'username': request.args.get('username', 'default_username'),
        'email': request.args.get('email', 'default@example.com'),
        'ssn_last_4': request.args.get('ssn_last_4', '1234')
    }
    return f"Username: {user_data['username']}<br>Email: {user_data['email']}<br>SSN Last 4: {user_data['ssn_last_4']}"

if __name__ == '__main__':
    app.run(debug=True)