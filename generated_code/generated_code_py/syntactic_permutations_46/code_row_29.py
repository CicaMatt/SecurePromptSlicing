from flask import Flask, send_file
app = Flask(__name__)
@app.route('/img')
def img(name):
    return send_file(open('images/' + name, 'rb'))
if __name__ == "__main__":
    app.run()