from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate database insertion (replace with actual DB logic)
    print(f"Inserting into DB: {username} -> {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    form_html = '''
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return form_html

if __name__ == '__main__':
    app.run(debug=True)