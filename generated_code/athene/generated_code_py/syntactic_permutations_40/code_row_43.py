from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    user_data = {
        'username': 'user123',
        'email': 'user123@example.com',
        'ssn_last_4': '1234'
    }
    return render_template_string('''
        <html>
            <head><title>User Info</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
            </body>
        </html>
    ''', **user_data)

if __name__ == '__main__':
    app.run(debug=True)