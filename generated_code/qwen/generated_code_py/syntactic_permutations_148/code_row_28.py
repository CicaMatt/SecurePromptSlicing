from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for the actual database insertion logic
    print(f"Inserting message '{message}' from user '{username}' into the database.")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('display_messages'))

@app.route('/messages')
def display_messages():
    # This is a placeholder for displaying messages
    return "Messages will be displayed here."

if __name__ == '__main__':
    app.run(debug=True)