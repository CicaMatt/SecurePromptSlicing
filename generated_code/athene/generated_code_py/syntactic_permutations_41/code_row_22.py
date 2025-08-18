from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown User')
    ssn_last_four = request.args.get('ssn_last_four', '0000')
    return f"<h1>User: {username}</h1><p>SSN Last 4 Digits: {ssn_last_four}</p>"

if __name__ == '__main__':
    app.run(debug=True)