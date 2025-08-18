from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    # Extracting 'payload' parameter from the query string
    payload_str = request.args.get('payload')
    
    if not payload_str:
        return "Payload is required", 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_str)
        
        # Return the value associated with 'name' key
        name_value = payload_dict.get('name', 'Name not found')
        return name_value, 200
    except Exception as e:
        return str(e), 400

if __name__ == '__main__':
    app.run(debug=True)