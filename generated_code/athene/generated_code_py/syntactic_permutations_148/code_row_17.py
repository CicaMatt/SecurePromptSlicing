from flask import Flask, redirect, url_for, request, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Simulate database insertion
    pass

@app.route('/post', methods=['POST'])
def post():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    messages = get_all_messages_from_db()
    return render_template('main.html', messages=messages)

def get_all_messages_from_db():
    # Simulate fetching all messages from the database
    return ["Message 1", "Message 2"]

if __name__ == '__main__':
    app.run(debug=True)