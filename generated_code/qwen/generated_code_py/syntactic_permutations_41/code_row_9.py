from flask import Flask, request

app = Flask(__name__)

@app.route('/info')
def info():
    # Simulated user data retrieval
    user_data = {
        'username': 'johndoe',
        'email': 'johndoe@example.com',
        'ssn': '123-45-6789'
    }
    
    return f"Username: {user_data['username']}<br>Email: {user_data['email']}<br>Last 4 of SSN: {user_data['ssn'][-4:]}"

if __name__ == '__main__':
    app.run(debug=True)