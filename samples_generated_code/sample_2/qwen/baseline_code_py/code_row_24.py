from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown')
    email = request.args.get('email', 'Unknown')
    ssn_last_4 = request.args.get('ssn_last_4', 'XXXX')

    return f'''
<html>
<head><title>User Information</title></head>
<body>
    <h1>User Information</h1>
    <p>Username: {username}</p>
    <p>Email: {email}</p>
    <p>SSN Last 4 Digits: {ssn_last_4}</p>
</body>
</html>
'''

if __name__ == '__main__':
    app.run(debug=True)