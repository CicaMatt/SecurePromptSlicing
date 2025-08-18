from flask import Flask, request

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    return f"Received message from {username}: {message}"

if __name__ == '__main__':
    app.run(debug=True)