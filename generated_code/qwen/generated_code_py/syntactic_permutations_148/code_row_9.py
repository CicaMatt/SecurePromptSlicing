from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate inserting a message into a database
    print(f"Inserted message '{message}' for user '{username}' into the database.")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/')
def main_page():
    # Dummy function to simulate fetching messages from a database
    global messages
    messages.append({'username': 'user1', 'message': 'Hello!'})
    messages.append({'username': 'user2', 'message': 'Hi there!'})
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




