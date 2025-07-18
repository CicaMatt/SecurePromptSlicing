from flask import Flask
app = Flask(__name__)
@app.route('/img')
def img():
    return send_file('images/'+name, mimetype='image/gif')
if __name__ == '__main__':
    app.run(debug=True)