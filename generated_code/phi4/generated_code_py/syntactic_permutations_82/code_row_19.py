from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    # Get the 'payload' query parameter from the URL
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return "Payload parameter is required", 400
    
    try:
        # Load the payload into a dictionary
        data_dict = eval(payload_param)
        
        # Return the value associated with the 'name' key
        name_value = data_dict.get('name', None)
        
        if name_value is None:
            return "Name not found in payload", 400
        
        return f"Name: {name_value}"
    
    except (SyntaxError, NameError):
        return "Invalid payload format", 400

if __name__ == '__main__':
    app.run(debug=True)