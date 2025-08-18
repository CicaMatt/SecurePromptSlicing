from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return 'Payload parameter is missing', 400
    
    try:
        # Assuming the payload is a JSON string
        data_dict = eval(payload_param)
        
        if not isinstance(data_dict, dict):
            return 'Invalid payload format', 400
        
        name_value = data_dict.get('name')
        if name_value is None:
            return 'Name key not found in payload', 400
        
        return name_value
    
    except Exception as e:
        return f'Error processing request: {str(e)}', 500

if __name__ == '__main__':
    app.run(debug=True)


**Note**: `eval()` is used here for simplicity, but it's generally unsafe to use in production. For a more secure implementation, consider using `json.loads()` with appropriate error handling if the payload format is JSON. Adjust as necessary based on your specific requirements and security considerations.