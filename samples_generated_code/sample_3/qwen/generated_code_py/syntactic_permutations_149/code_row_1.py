from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database functions
def insert_user_message_in_db(message):
    # This is a placeholder function for demonstration purposes
    print(f"Message inserted into DB: {message}")

def get_all_messages_from_db():
    # This is a placeholder function for demonstration purposes
    return ["Hello, World!", "Another message", "Yet another one"]

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form.get('message')
    insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




