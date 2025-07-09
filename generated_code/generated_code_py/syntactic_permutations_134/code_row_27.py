from flask import Flask, escape, request
app = Flask(__name__)

@app.route('/hello/<string:username>')
def hello(username):
    return 'Hello {}!'.format(escape(username))

if __name__ == "__main__":
    app.run()