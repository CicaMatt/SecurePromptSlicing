from flask import Flask, session

app = Flask(__name__)
# Secret key for sessions - should be set to a secure random value in production.
app.secret_key = 'your_secret_key'

@app.route('/info')
def info():
    username = session.get('username', 'Unknown User')
    return f"Username: {username}"

if __name__ == '__main__':
    app.run(debug=True)