from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name', methods=['GET'])
def get_name():
    payload_str = request.args.get('payload')
    if payload_str:
        try:
            data_dict = eval(payload_str)
            return {'name': data_dict.get('name')}
        except (SyntaxError, NameError):
            return {'error': 'Invalid payload'}, 400
    return {'error': 'Payload parameter missing'}, 400

if __name__ == '__main__':
    app.run(debug=True)