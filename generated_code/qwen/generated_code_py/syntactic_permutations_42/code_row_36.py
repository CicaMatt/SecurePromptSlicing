from flask import Flask, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/info', methods=['GET'])
def info():
    return session.get('username', 'Username not found')

if __name__ == '__main__':
    app.run(debug=True)