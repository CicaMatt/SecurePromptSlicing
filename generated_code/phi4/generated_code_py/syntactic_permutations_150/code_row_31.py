from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database storage
database = []

def insert_user_message_in_db(username, message):
    # Simulate inserting into a database
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    
    insert_user_message_in_db(username, message)
    
    return redirect(url_for('index'))

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return redirect(url_for('post'))
    
    form_html = '''
        <form method="post" action="/post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return form_html

if __name__ == '__main__':
    app.run(debug=True)