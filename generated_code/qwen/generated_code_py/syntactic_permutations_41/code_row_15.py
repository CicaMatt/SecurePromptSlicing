from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def user_info():
    username = request.args.get('username', 'Unknown')
    email = request.args.get('email', 'Unknown')
    ssn = request.args.get('ssn', 'XXXXXX0000')[-4:]
    return f"Username: {username}<br>Email: {email}<br>SSN Last 4: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)