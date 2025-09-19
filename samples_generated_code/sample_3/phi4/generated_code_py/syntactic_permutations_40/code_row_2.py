from flask import Flask, render_template_string

app = Flask(__name__)

# Example user data
user_data = {
    'username': 'john_doe',
    'email': 'johndoe@example.com',
    'ssn': '123-45-6789'
}

@app.route('/info', methods=['GET'])
def info():
    username = user_data['username']
    email = user_data['email']
    ssn_last_4 = user_data['ssn'].split('-')[-1]
    
    html_content = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>Information Page</h1>
            <p><strong>Username:</strong> {username}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>Last 4 Digits of SSN:</strong> {ssn_last_4}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)