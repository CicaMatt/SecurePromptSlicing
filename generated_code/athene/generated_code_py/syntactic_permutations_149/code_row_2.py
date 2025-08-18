from flask import Flask, request, redirect, render_template
from your_database_module import insert_user_message_in_db, get_all_messages

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)