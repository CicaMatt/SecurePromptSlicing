from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', 'No Email Provided')
    ssn = request.args.get('ssn', '0000')

    return render_template_string('''
        <html>
            <head><title>User Info</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Last 4 Digits of SSN: {{ ssn }}</p>
            </body>
        </html>
    ''', username=username, email=email, ssn=ssn)

if __name__ == '__main__':
    app.run(debug=True)