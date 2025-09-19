from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # This is a placeholder function for inserting data into a database.
    # Replace this with actual database insertion logic.
    print(f"Inserted message: {message} from {name}")

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    insert_user_message_in_db(name, message)
    return redirect('/')

def get_messages_from_db():
    # This is a placeholder function for retrieving data from a database.
    # Replace this with actual database retrieval logic.
    return [
        {'name': 'Alice', 'message': 'Hello!'},
        {'name': 'Bob', 'message': 'Hi there!'}
    ]

@app.route('/')
def index():
    messages = get_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




