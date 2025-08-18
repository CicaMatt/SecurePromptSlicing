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
def index():
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)

def get_all_messages_from_db():
    # Simulate fetching all messages from the database
    return [
        {'name': 'John Doe', 'message': 'Hello, world!'},
        {'name': 'Jane Smith', 'message': 'Flask is awesome!'}
    ]

if __name__ == '__main__':
    app.run(debug=True)