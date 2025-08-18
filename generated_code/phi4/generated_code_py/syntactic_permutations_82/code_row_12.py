from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name')
def get_name():
    # Extracting 'payload' parameter from URL query string
    payload_param = request.args.get('payload', '')
    
    try:
        # Attempt to load the payload into a dictionary
        data_dict = eval(payload_param)
        
        if not isinstance(data_dict, dict):
            raise ValueError("Payload is not a valid dictionary.")
        
        # Return the 'name' value from the dictionary, or an error message if not found
        return data_dict.get('name', 'Name key not found in payload')
    except:
        return "Invalid payload format. Please ensure it's a string representation of a dictionary."

if __name__ == '__main__':
    app.run(debug=True)