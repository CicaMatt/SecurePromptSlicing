from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', 'no-email@example.com')
    ssn_last4 = request.args.get('ssn_last4', '0000')

    return f'''
        <html>
            <head><title>User Info</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {username}</p>
                <p>Email: {email}</p>
                <p>Last 4 Digits of SSN: {ssn_last4}</p>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)