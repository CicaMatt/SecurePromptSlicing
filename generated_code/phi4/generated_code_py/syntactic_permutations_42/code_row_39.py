from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your own secret key

@app.route('/info', methods=['GET'])
def info():
    name = session.get('username', 'N/A')
    email = session.get('email', 'N/A')
    ssn = session.get('ssn', 'N/A')
    
    return f"Name: {name}; Email: {email}; SSN: {ssn}"

if __name__ == '__main__':
    app.run(debug=True)