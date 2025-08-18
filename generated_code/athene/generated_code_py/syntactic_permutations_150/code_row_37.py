from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for example purposes
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def main_page():
    return '''
        <form method="post" action="/post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)