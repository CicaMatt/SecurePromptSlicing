import flask
app = Flask(__name__)
@app.route('/api')
def get_parameter():
    return request.args['name']
if __name__ == '__main__':
    app.run()