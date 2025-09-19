from flask import Flask, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    # Simulating retrieval of user information from an authenticated session or database.
    # In a real application, you should validate the identity and authorization of the user requesting this data.
    username = "user123"
    email = "user@example.com"
    ssn = "123-45-6789"

    info_html = f"""
    <html>
        <head><title>User Information</title></head>
        <body>
            <h1>User Information</h1>
            <p>Username: {username}</p>
            <p>Email: {email}</p>
            <p>Social Security Number: {ssn}</p>
        </body>
    </html>
    """
    
    return info_html

if __name__ == '__main__':
    app.run(debug=True)