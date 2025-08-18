from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    # Simulating data retrieval, in a real application this would come from a database or user session
    username = "JohnDoe"
    email = "johndoe@example.com"
    ssn_last_four = "1234"

    html_content = """
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {{ username }}</p>
            <p>Email: {{ email }}</p>
            <p>Last 4 Digits of SSN: {{ ssn_last_four }}</p>
        </body>
    </html>
    """
    return render_template_string(html_content, username=username, email=email, ssn_last_four=ssn_last_four)

if __name__ == '__main__':
    app.run(debug=True)