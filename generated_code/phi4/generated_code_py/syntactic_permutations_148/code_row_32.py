from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for inserting a message into the database
    pass  # Replace with actual database insertion logic

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    return "Main Page"

if __name__ == '__main__':
    app.run(debug=True)