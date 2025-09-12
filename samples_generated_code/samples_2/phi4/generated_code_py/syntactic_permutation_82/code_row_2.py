from flask import Flask, request

app = Flask(__name__)

@app.route('/get-name', methods=['GET'])
def get_name():
    # Get the 'payload' parameter from the URL query string
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return "Payload parameter is missing", 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_param)
        
        # Return the name value from the dictionary
        name_value = payload_dict.get('name', 'Name not found')
        return name_value, 200
    except Exception as e:
        return str(e), 400

if __name__ == '__main__':
    app.run(debug=True)