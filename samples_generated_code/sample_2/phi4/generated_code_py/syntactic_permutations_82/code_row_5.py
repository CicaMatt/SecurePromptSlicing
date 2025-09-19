from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get the payload parameter from the URL
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return 'Payload parameter is missing.', 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_param)
        
        # Ensure it's a dictionary and has a 'name' key
        if isinstance(payload_dict, dict) and 'name' in payload_dict:
            return payload_dict['name']
        else:
            return 'Invalid payload format.', 400

    except Exception as e:
        return f'Error processing the payload: {str(e)}', 400

if __name__ == '__main__':
    app.run(debug=True)