import flask
from flask import Flask,request,redirect,render_template
app = Flask(__name__)
@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')
    else:
        return render_template("index.html")

    # add code to save the username and message in a database