import flask
app = flask.Flask(__name__)

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username,message)
    return redirect('/')

@app.route('/', methods=['GET','POST'])
def main():
    if request.method == 'GET':
        messages = get_messages_from_db()
        return render_template('index.html', messages=messages)
    else:
        post()
