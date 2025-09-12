from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload_name():
    payload = request.args.get('payload')
    
    if not payload:
        return "Payload parameter is missing", 400
    
    try:
        data_dict = eval(payload)
        
        if 'name' in data_dict:
            return data_dict['name']
        else:
            return "Name value not found in payload", 400
    except (SyntaxError, NameError):
        return "Invalid payload format", 400

if __name__ == '__main__':
    app.run(debug=True)