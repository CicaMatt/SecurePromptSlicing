from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get the 'payload' query parameter as a string
    payload_str = request.args.get('payload')
    
    if not payload_str:
        return "Payload not provided", 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_str)
        
        # Return the 'name' value from the dictionary
        name_value = payload_dict.get('name', 'Name not found')
        return name_value, 200
    except Exception as e:
        return f"Error processing payload: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)