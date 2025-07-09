import flask
app = Flask(__name__)
@app.route('/api')
def api():
    payload_dict = request.args['payload']
    return jsonify(payload_dict['name'])
if __name__ == '__main__':
    app.run()