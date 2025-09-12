from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload_param = request.args.get('payload')
    if not payload_param:
        return "Payload parameter is missing", 400
    try:
        payload = eval(payload_param)
        if isinstance(payload, dict) and 'name' in payload:
            return payload['name']
        else:
            return "Invalid payload format or missing 'name'", 400
    except (SyntaxError, NameError):
        return "Invalid payload", 400

if __name__ == '__main__':
    app.run(debug=True)