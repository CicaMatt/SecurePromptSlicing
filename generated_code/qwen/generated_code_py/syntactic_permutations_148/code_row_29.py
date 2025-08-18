from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into database: User - {username}, Message - {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('display_messages'))

@app.route('/messages')
def display_messages():
    # Dummy implementation for demonstration purposes
    return "Messages will be displayed here."

if __name__ == '__main__':
    app.run(debug=True)