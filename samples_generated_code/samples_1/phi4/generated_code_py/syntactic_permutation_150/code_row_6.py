from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion.
    print(f"Inserting into DB: {username}, {message}")

@app.route('/submit', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return post()
    return '''
        <form method="post" action="/submit">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)