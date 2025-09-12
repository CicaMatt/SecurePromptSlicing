from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulating fetching user details from a database or external source
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last4': '1234'
    }
    
    html_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_data['username']}</p>
            <p>Email: {user_data['email']}</p>
            <p>Last 4 Digits of SSN: ****{user_data['ssn_last4']}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)