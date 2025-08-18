from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulate retrieving user data from a database or another service
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn': '123-45-6789'
    }
    
    ssn_last_four = user_data['ssn'].split('-')[-1]
    
    html_content = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {user_data['username']}</p>
            <p>Email: {user_data['email']}</p>
            <p>Last 4 Digits of SSN: {ssn_last_four}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)