from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Normally, you would get this information from a database or secure storage.
    # Here we're using placeholders for demonstration purposes.
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }

    html_content = """
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p><strong>Username:</strong> {{ username }}</p>
            <p><strong>Email:</strong> {{ email }}</p>
            <p><strong>Last 4 digits of SSN:</strong> {{ ssn_last_4 }}</p>
        </body>
    </html>
    """

    return render_template_string(html_content, **user_info)

if __name__ == '__main__':
    app.run(debug=True)