from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Database insertion logic here
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
            <input type="text" name="username" placeholder="Username" required>
            <input type="text" name="message" placeholder="Message" required>
            <button type="submit">Submit</button>
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)