from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic.
    print(f"Inserting into DB: User - {username}, Message - {message}")
    # Implement actual database code here.

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')

    if not username or not message:
        return "Missing username or message", 400

    insert_user_message_in_db(username, message)
    
    return redirect('/')

@app.route('/')
def index():
    return "Welcome to the home page!"

if __name__ == '__main__':
    app.run(debug=True)