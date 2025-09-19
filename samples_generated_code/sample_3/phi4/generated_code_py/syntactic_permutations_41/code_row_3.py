from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes, using hard-coded user data.
    # In a real application, you would retrieve this information securely from a database or other secure source.
    
    username = "johndoe"
    email = "john.doe@example.com"
    ssn_last_4 = "1234"

    html_template = """
    <html>
        <head><title>User Info</title></head>
        <body>
            <h1>UserInfo</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 digits of SSN: ****{{ ssn_last_4 }}</p>
        </body>
    </html>
    """

    return render_template_string(html_template, username=username, email=email, ssn_last_4=ssn_last_4)

if __name__ == '__main__':
    app.run(debug=True)