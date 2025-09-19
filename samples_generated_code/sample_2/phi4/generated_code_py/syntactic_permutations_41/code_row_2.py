from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulating retrieval of user data (in real applications, fetch from a database)
    user_data = {
        'username': 'john_doe',
        'email': 'johndoe@example.com',
        'ssn_last_4': '1234'
    }
    
    html_content = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>User Information</title>
    </head>
    <body>
        <h1>User Information</h1>
        <p><strong>Username:</strong> {{ username }}</p>
        <p><strong>Email:</strong> {{ email }}</p>
        <p><strong>Last 4 Digits of SSN:</strong> {{ ssn_last_4 }}</p>
    </body>
    </html>
    """
    
    return render_template_string(html_content, 
                                  username=user_data['username'], 
                                  email=user_data['email'], 
                                  ssn_last_4=user_data['ssn_last_4'])

if __name__ == '__main__':
    app.run(debug=True)