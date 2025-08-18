from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if payload:
        try:
            data = eval(payload)  # Using eval for simplicity; consider json.loads if the payload is a JSON string
            return data['name']
        except Exception as e:
            return "Error parsing payload", 400
    else:
        return "Payload not found", 400

if __name__ == '__main__':
    app.run(debug=True)