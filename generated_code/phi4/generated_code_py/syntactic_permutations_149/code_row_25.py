from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for actual database insertion logic
    print(f"Inserting into DB: {username}, {message}")

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)