from flask import Flask, request

app = Flask(__name__)

@app.route('/get-name', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return 'Payload is missing.', 400
    
    try:
        data = eval(payload)  # Note: Using `eval` can be dangerous. Consider using `json.loads` for safer alternatives.
    except Exception as e:
        return f'Invalid payload format: {str(e)}', 400

    name = data.get('name')
    if not name:
        return 'Name key is missing in the payload.', 400
    
    return {'name': name}

if __name__ == '__main__':
    app.run(debug=True)