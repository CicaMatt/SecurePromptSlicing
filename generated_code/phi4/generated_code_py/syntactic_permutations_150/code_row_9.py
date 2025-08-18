from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    print(f"Inserting into DB: {username} says {message}")

@app.route('/submit', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    form_html = '''
    <html>
        <body>
            <form action="/submit" method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    '''
    return form_html

if __name__ == '__main__':
    app.run(debug=True)