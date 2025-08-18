from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate database insertion
    pass

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('display_messages'))

@app.route('/')
def display_messages():
    # Simulate fetching and displaying messages
    return "Messages displayed here"

if __name__ == '__main__':
    app.run(debug=True)