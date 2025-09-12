from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Not Available')
    email = session.get('email', 'Not Available')
    ssn_last_4 = session.get('ssn_last_4', 'Not Available')
    
    return f'''
    <html>
        <body>
            <h1>Information</h1>
            <p><strong>Username:</strong> {username}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>Last 4 digits of SSN:</strong> {ssn_last_4}</p>
        </body>
    </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)