import flask

app = flask.Flask(__name__)

@app.route('/', methods=['POST'])
def get_username():
    username = flask.request.form['username']
    return 'Hello {}'.format(username)

if __name__ == '__main__':
    app.run()