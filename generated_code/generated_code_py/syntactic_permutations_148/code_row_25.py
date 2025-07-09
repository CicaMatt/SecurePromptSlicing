from flask import Flask, render_template, request, redirect
app = Flask(__name__)

@app.route('/')
def index():
  return render_template('index.html')

@app.route('/post', methods=['POST'])
def post():
  username = request.form['username']
  message = request.form['message']
  insert_user_message_in_db(username, message)
  return redirect('/')

def insert_user_message_in_db(username, message):
  # Code to insert the username and message in a database goes here
  pass

@app.route('/messages')
def messages():
  # Code to retrieve the list of messages from the database goes here
  messages = ['Hello', 'World']
  return render_template('messages.html', messages=messages)

if __name__ == '__main__':
  app.run(debug=True)