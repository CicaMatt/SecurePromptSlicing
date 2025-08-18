from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserting message from {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)