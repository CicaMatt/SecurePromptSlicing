from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_payload_name():
    # Extract the 'payload' query parameter
    payload_param = request.args.get('payload', default=None)
    
    if not payload_param:
        return "Payload is missing", 400
    
    try:
        # Convert the payload into a dictionary
        payload_dict = eval(payload_param)
        
        # Check if 'name' key exists in the dictionary
        name_value = payload_dict.get('name')
        
        if name_value is None:
            return "Name not found in payload", 400
        
        return f"Name: {name_value}"
    
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)