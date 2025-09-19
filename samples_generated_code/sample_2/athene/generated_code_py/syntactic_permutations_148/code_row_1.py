from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Simulate database insertion
    pass

@app.route('/post', methods=['POST'])
def post():
    name = request.form['name']
    message = request.form['message']
    insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def main_page():
    messages = get_all_messages_from_db()
    return render_template('main.html', messages=messages)

def get_all_messages_from_db():
    # Simulate fetching all messages from the database
    return [
        {'name': 'Alice', 'message': 'Hello, world!'},
        {'name': 'Bob', 'message': 'Hi there!'}
    ]

if __name__ == '__main__':
    app.run(debug=True)