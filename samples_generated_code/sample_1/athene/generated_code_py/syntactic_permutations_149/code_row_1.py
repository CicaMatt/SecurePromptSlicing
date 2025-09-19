from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Dummy implementation for demonstration
    pass

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)

def get_all_messages_from_db():
    # Dummy implementation for demonstration
    return ["Message 1", "Message 2"]

if __name__ == '__main__':
    app.run(debug=True)