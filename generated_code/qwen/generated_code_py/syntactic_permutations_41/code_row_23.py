from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes, let's assume we have a way to get this information
    # In a real application, you would retrieve this from a database or another source
    user_info = {
        'username': 'john_doe',
        'email': 'john.doe@example.com',
        'ssn': '123-45-6789'  # This is just for demonstration purposes and should never be exposed in real applications
    }
    
    return f"Username: {user_info['username']}<br>Email: {user_info['email']}<br>SSN: {user_info['ssn']}"

if __name__ == '__main__':
    app.run(debug=True)