from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def index():
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', 'no-reply@example.com')
    ssn_last4 = request.args.get('ssn', '0000')[-4:]
    
    return f'''
        <html>
            <body>
                <h1>Welcome, {username}!</h1>
                <p>Email: {email}</p>
                <p>Last 4 digits of SSN: {ssn_last4}</p>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)