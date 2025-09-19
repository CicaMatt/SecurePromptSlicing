from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # This is just a mock implementation for demonstration purposes.
    # In a real-world application, you would retrieve this information from a database or another source.
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'social_security_number': '123-45-6789'
    }
    return f"Username: {user_info['username']}<br>Email: {user_info['email']}<br>Social Security Number: {user_info['social_security_number']}"

if __name__ == '__main__':
    app.run(debug=True)