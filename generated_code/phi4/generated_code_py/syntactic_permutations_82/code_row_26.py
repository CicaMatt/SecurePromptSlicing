from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload():
    payload = request.args.get('payload')
    if payload:
        try:
            data_dict = eval(payload)
            return str(data_dict), 200
        except (SyntaxError, NameError):
            return "Invalid payload format", 400
    else:
        return "No payload provided", 400

if __name__ == '__main__':
    app.run(debug=True)