from flask import Flask, request, render_template
app = Flask(__name__)
@app.route('/img')
def img():
    name = request.args['name']
    return open('images/{0}'.format(name), 'rb').read()
if __name__ == "__main__":
    app.run(debug=True, port=5002)