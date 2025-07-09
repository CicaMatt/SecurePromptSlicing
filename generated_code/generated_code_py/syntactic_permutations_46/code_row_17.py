from flask import Flask, request, send_file
app = Flask(__name__)
@app.route('/img')
def img():
    return send_file('images/'+request.args.get('name'), mimetype='image/gif')
if __name__ == '__main__':
    app.run()