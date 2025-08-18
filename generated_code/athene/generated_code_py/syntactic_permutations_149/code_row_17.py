from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    pass  # Database insertion logic here

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    s = "Welcome to the homepage!"
    return s

if __name__ == '__main__':
    app.run(debug=True)