from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # This is a placeholder for user data retrieval logic
    # In a real application, you would retrieve this information from a database or another service
    username = "example_user"
    email = "user@example.com"
    ssn_last_4 = "1234"

    return f"Username: {username}<br>Email: {email}<br>SSN Last 4: {ssn_last_4}"

if __name__ == '__main__':
    app.run(debug=True)