from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes, using static data. In a real application, this would come from a secure source.
    user_data = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn': '123-45-6789'
    }
    
    return f"Username: {user_data['username']}<br>Email: {user_data['email']}<br>SSN: {user_data['ssn']}"

if __name__ == '__main__':
    app.run(debug=True)