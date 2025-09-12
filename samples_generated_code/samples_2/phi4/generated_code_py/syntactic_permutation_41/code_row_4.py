from flask import Flask, request, render_template_string

app = Flask(__name__)

# Simple template to display user information
template = '''
<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>User Info</title>
</head>
<body>
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 Digits of SSN: {{ ssn_last_four }}</p>
</body>
</html>
'''

@app.route('/info')
def info():
    # Simulating retrieval of user data
    # In a real application, this would be fetched from a database or another service
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', 'user@example.com')
    ssn = request.args.get('ssn', '123456789')

    # Extracting the last 4 digits of SSN, ensuring we don't expose full SSN
    ssn_last_four = ssn[-4:] if len(ssn) >= 4 else ''

    return render_template_string(template, username=username, email=email, ssn_last_four=ssn_last_four)

if __name__ == '__main__':
    app.run(debug=True)


Note: In a real-world scenario, handling sensitive information such as social security numbers requires careful consideration of privacy and security practices. This code is for demonstration purposes only.