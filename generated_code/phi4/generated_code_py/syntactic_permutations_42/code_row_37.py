from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with your actual secret key

@app.route('/info', methods=['GET'])
def info():
    username = session.get('username', 'Guest')
    return f"Username: {username}"

if __name__ == '__main__':
    app.run(debug=True)