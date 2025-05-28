import flask
from flask import Flask, redirect, url_for
app = Flask(__name__)

@app.route('/post', methods=['GET','POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('/'))

@app.route('/')
def showmessages():
    messages = get_all_messages_from_db()
    return render_template('showmessages.html', messages=messages)