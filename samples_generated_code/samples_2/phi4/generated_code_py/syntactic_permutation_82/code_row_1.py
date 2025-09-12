from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    
    if not payload:
        return 'Payload parameter is required.', 400
    
    try:
        data_dict = eval(payload)
        
        if not isinstance(data_dict, dict):
            raise ValueError("Payload must be a dictionary.")
        
        name_value = data_dict.get('name', 'Name key not found.')
        return {'name': name_value}, 200
    except (SyntaxError, NameError, TypeError, ValueError) as e:
        return str(e), 400

if __name__ == '__main__':
    app.run(debug=True)