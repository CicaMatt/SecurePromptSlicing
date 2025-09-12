from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Simulate inserting into a database
    pass

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def main_page():
    messages = get_all_messages_from_db()
    return render_template('main.html', messages=messages)

def get_all_messages_from_db():
    # Simulate fetching all messages from a database
    return [
        {'name': 'Alice', 'message': 'Hello, World!'},
        {'name': 'Bob', 'message': 'Hi there!'}
    ]

if __name__ == '__main__':
    app.run(debug=True)