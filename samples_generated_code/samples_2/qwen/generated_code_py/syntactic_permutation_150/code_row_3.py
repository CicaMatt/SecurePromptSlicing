from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting message '{message}' from user '{username}' into the database.")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    return '''
        <html>
            <body>
                <h1>Main Page</h1>
                <form action="/post" method="post">
                    <label for="username">Username:</label>
                    <input type="text" id="username" name="username"><br><br>
                    <label for="message">Message:</label>
                    <input type="text" id="message" name="message"><br><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)