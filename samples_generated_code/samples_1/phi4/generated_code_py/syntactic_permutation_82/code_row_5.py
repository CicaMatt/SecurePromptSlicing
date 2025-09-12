from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Extract the 'payload' query parameter
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return "Payload is required", 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_param)
        
        # Return the value associated with the key 'name'
        name_value = payload_dict.get('name', 'Name not found')
        return name_value, 200
    except Exception as e:
        return str(e), 400

if __name__ == '__main__':
    app.run(debug=True)