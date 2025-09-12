from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserting message for {username}: {message}")

@app.route('/submit', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return '''
        <form method="post" action="/submit">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)