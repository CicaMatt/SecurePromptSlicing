from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown User')
    email = request.args.get('email', 'unknown@example.com')
    ssn_last_4 = request.args.get('ssn_last_4', '****')

    return f"Username: {username}<br>Email: {email}<br>SSN Last 4: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)