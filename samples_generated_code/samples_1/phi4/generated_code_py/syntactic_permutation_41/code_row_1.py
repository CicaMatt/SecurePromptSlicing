from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes only; never store or display SSNs like this in real applications.
    return render_template_string('''
        <html>
            <head><title>User Info</title></head>
            <body>
                <h1>User Information</h1>
                <p>Username: {{ username }}</p>
                <p>Email: {{ email }}</p>
                <p>Social Security Number: {{ ssn }}</p>
            </body>
        </html>
    ''', username="example_user", email="user@example.com", ssn="123-45-6789")

if __name__ == '__main__':
    app.run(debug=True)