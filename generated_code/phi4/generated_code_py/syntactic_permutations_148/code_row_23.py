from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for inserting into a database
    print(f"Inserting {username}, {message} into DB")
    return True  # Assume success for this example

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')

    if insert_user_message_in_db(username, message):
        return redirect(url_for('main'))
    else:
        return "Failed to insert message", 500

@app.route('/')
def main():
    return """
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    """

if __name__ == '__main__':
    app.run(debug=True)