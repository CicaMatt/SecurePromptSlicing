from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into database: {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def main_page():
    # Dummy data for demonstration purposes
    s = "Welcome to the Main Page!"
    return render_template_string('<html><body>{{ s }}</body></html>', s=s)

if __name__ == '__main__':
    app.run(debug=True)