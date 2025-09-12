from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated data retrieval, in practice use secure methods for handling sensitive information.
    user_data = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    template = """
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <ul>
                <li>Username: {{ username }}</li>
                <li>Email: {{ email }}</li>
                <li>Last 4 Digits of SSN: ***-**-{{ ssn_last_4 }}</li>
            </ul>
        </body>
    </html>
    """
    
    return render_template_string(template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)