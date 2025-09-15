from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting message into database: {message}")

@app.route('/post', methods=['POST'])
def post():
    user_message = request.form.get('message')
    if user_message:
        insert_user_message_in_db(user_message)
    return redirect('/')

messages = [
    "Hello, world!",
    "Welcome to the message board."
]

@app.route('/')
def index():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




