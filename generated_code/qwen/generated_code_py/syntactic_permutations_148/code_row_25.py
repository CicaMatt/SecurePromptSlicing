from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for the actual database insertion logic
    print(f"Inserting message: {message} from user: {username}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/')
def main_page():
    # This is a placeholder for fetching messages from the database
    global messages
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




