from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for example purposes
    pass

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('display_messages'))

@app.route('/messages')
def display_messages():
    # Dummy implementation for example purposes
    return "Messages would be displayed here."

if __name__ == '__main__':
    app.run(debug=True)