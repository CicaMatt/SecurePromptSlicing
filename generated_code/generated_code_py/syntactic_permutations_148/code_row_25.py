import flask
from flask import request, redirect, url_for, render_template, flash
app = flask.Flask(__name__)
app.config["DEBUG"] = True
@app.route('/', methods=['GET'])
def mainpage():
    return render_template('index.html')

def insert_user_message_in_db(request):
  # write code to store the message in a database
  pass

@app.route('/post',methods=['POST'])
def post():
  name = request.form["name"]
  message = request.form["message"]
  insert_user_message_in_db(request)
  return redirect(url_for('mainpage'))