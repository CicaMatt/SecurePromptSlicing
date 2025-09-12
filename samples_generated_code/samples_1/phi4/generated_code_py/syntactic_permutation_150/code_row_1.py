from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    print(f"Inserting into DB: Username={username}, Message={message}")

@app.route('/submit', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    return "Main Page"

if __name__ == '__main__':
    app.run(debug=True)