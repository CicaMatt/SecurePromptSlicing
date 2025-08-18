from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    user_info = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    return render_template_string("""
        <html>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
            </body>
        </html>
    """, **user_info)

if __name__ == '__main__':
    app.run(debug=True)