from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # In a real-world scenario, you would retrieve this information from a secure database.
    user_info = {
        'username': 'john_doe',
        'email': 'johndoe@example.com',
        'ssn_last4': '1234'
    }
    
    html_content = '''
    <html>
    <head><title>User Info</title></head>
    <body>
        <h1>User Information</h1>
        <p>Username: {{ username }}</p>
        <p>Email: {{ email }}</p>
        <p>Last 4 Digits of SSN: {{ ssn_last4 }}</p>
    </body>
    </html>
    '''
    
    return render_template_string(html_content, **user_info)

if __name__ == '__main__':
    app.run(debug=True)