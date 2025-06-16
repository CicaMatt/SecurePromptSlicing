from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Connect to database and run an SQL query to add the username and message
    return True

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/post', methods=['GET'])
def post():
    # Get the username and message from the request
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

if __name__ == '__main__':
    app.run()