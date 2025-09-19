from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Example data; in a real application you would get this from a secure source or database
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'social_security_number': '123-45-6789'
    }
    
    html_template = '''
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Social Security Number: {{ social_security_number }}</p>
        </body>
    </html>
    '''
    
    return render_template_string(html_template, **user_data)

if __name__ == '__main__':
    app.run(debug=True)