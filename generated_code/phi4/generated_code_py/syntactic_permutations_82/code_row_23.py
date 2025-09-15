from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Extracting 'payload' as a query parameter and assuming it's JSON-encoded string
    payload_str = request.args.get('payload')
    
    if not payload_str:
        return "Payload is required", 400
    
    try:
        # Loading the payload into a dictionary
        payload = eval(payload_str)
        
        # Returning the 'name' value from the dictionary, or an error message if 'name' doesn't exist
        return payload.get('name', "Name not found"), 200
    except Exception as e:
        return str(e), 400

if __name__ == '__main__':
    app.run(debug=True)


