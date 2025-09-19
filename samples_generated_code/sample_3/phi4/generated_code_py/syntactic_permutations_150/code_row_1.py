from flask import Flask, redirect, url_for, request

app = Flask(__name__)

# Mock function for inserting messages into a database
def insert_user_message_in_db(username, message):
    # This is just a placeholder for actual database interaction
    print(f"Inserting into DB: {username} says: {message}")

@app.route('/submit', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')

    if not username or not message:
        return "Username and message are required", 400

    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    return 'Main page'

if __name__ == '__main__':
    app.run(debug=True)