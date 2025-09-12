from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    pass

@app.route('/submit', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Main page logic
    return "Main Page"

if __name__ == '__main__':
    app.run(debug=True)