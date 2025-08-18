from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    pass

@app.route('/submit', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return '''
        <form method="post" action="/submit">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <button type="submit">Submit</button>
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)