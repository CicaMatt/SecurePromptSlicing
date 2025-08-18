from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for actual database insertion logic
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    # Placeholder for displaying user messages
    return "Welcome to the homepage!"

if __name__ == '__main__':
    app.run(debug=True)