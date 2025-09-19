from flask import Flask, render_template_string

app = Flask(__name__)

# Sample user data
user_data = {
    'username': 'john_doe',
    'email': 'john.doe@example.com',
    'ssn': '123-45-6789'
}

@app.route('/info', methods=['GET'])
def info():
    username = user_data['username']
    email = user_data['email']
    ssn_last_4 = user_data['ssn'].split('-')[-1]
    
    html_content = f"""
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 digits of SSN: {ssn_last_4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)