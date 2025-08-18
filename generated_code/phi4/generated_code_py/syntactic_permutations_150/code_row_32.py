from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Assume this is a placeholder for your database interaction logic.
def insert_user_message_in_db(username, message):
    # Here you would have logic to insert the username and message into a database.
    pass

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        return post()
    
    return render_template_string('''
        <form method="post" action="/">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main_page'))

if __name__ == '__main__':
    app.run(debug=True)