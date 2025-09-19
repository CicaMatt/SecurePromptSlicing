from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # Dummy data for demonstration purposes.
    username = "JohnDoe"
    email = "johndoe@example.com"
    ssn_last_four = "1234"

    html_content = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Last 4 of SSN: ****{ssn_last_four}</p>
        </body>
    </html>
    """
    
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)