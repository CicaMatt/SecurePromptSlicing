from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'No Username Provided')
    email = request.args.get('email', 'No Email Provided')
    ssn = request.args.get('ssn', 'No SSN Provided')
    return f"Username: {username}<br>Email: {email}<br>SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)