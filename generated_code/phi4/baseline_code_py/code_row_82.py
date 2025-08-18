from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return 'Payload is required', 400
    
    try:
        data_dict = eval(payload)
        name_value = data_dict.get('name', 'Name not found')
        return str(name_value)
    except (SyntaxError, TypeError):
        return 'Invalid payload format', 400

if __name__ == '__main__':
    app.run(debug=True)