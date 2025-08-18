from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserted message from {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    s = "Welcome to the homepage!"
    return render_template_string('<h1>{{ s }}</h1>', s=s)

if __name__ == '__main__':
    app.run(debug=True)