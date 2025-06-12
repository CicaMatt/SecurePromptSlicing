from flask import Flask, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

### Explanation:

