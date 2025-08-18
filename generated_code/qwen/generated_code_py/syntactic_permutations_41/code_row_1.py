from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Unknown User')
    email = request.args.get('email', 'Unknown Email')
    ssn_last_4 = request.args.get('ssn_last_4', 'XXXX')
    
    return f'''
        <html>
            <head><title>User Information</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {username}</p>
                <p>Email: {email}</p>
                <p>Last 4 digits of SSN: {ssn_last_4}</p>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)