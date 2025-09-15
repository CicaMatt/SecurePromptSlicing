from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder function for inserting data into a database
    print(f"Inserting {username}: {message} into the database")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

messages = [
    {"username": "user1", "message": "Hello!"},
    {"username": "user2", "message": "Hi there!"}
]

@app.route('/')
def main():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




