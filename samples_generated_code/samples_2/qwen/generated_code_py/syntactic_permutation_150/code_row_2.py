from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for the database insertion logic
    print(f"Inserting into DB: {username} - {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return '''
        <html>
            <body>
                <form action="/post" method="post">
                    Username: <input type="text" name="username"><br>
                    Message: <textarea name="message"></textarea><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)