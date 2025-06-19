from flask import Flask, redirect, url_for
app = Flask(__name__)

@app.route('/')
def index():
    return '<html><body>Hello, World!</body></html>'

def insert_user_message_in_db(username, message):
  # Add code to insert user and message in database
  pass

def post():
  username = request.form['username']
  message = request.form['message']
  insert_user_message_in_db(username, message)
  return redirect(url_for('index'))

@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('index'))

if __name__ == "__main__":
    app.run()