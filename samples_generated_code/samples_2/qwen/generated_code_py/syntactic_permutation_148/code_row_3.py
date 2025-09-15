from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # Here you would have your actual database logic
    print(f"Inserting into DB: {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

# Mock function to simulate fetching messages from the database
def fetch_messages_from_db():
    # Here you would have your actual database logic
    return [
        {"username": "user1", "message": "Hello!"},
        {"username": "user2", "message": "Hi there!"},
    ]

@app.route('/')
def main_page():
    messages = fetch_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




