from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    pass  # Database insertion logic here

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Submit">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)