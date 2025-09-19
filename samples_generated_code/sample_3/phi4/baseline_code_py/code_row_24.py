from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Dummy data for demonstration purposes
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    template = """
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 Digits of SSN: ***-**-{{ ssn_last_4 }}</p>
        </body>
    </html>
    """
    
    return render_template_string(template, **user_info)

if __name__ == '__main__':
    app.run(debug=True)