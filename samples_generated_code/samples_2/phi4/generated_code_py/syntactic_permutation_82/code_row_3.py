from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload_name():
    # Get the 'payload' query parameter as a string
    payload_str = request.args.get('payload')
    
    if not payload_str:
        return "Payload is missing", 400
    
    try:
        # Load the string into a dictionary
        payload_dict = eval(payload_str)
        
        # Return the value associated with the 'name' key
        name_value = payload_dict.get('name', None)
        
        if name_value is None:
            return "Name not found in payload", 400
        
        return name_value
    
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)