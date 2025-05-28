import flask
from flask import request, redirect

app = flask.Flask(__name__)
app.config["DEBUG"] = True

def insert_user_message_in_db(username, message):
    pass

@app.route('/', methods=['GET'])
def home():
    return """
        <html>
            <body>
                <h1>Home Page</h1>
                <form action="/post" method="POST">
                    <label for="username">Username: </label>
                    <input type="text" name="username"><br>
                    <label for="message">Message: </label>
                    <textarea name="message"></textarea><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    """

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect("/")

app.run()