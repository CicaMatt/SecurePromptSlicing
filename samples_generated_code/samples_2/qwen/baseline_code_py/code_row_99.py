from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into DB: {username}: {message}")
    # Here you would have your actual database insertion logic

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

def get_messages_from_db():
    # Dummy implementation for demonstration purposes
    global messages
    return messages

@app.route('/')
def main_page():
    messages = get_messages_from_db()
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




