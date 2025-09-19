from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown User')
    email = request.args.get('email', 'Unknown Email')
    ssn = request.args.get('ssn', 'Unknown SSN')
    return f"Username: {username}<br>Email: {email}<br>SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)