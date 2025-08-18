from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get the 'payload' query parameter as a JSON string
    payload_str = request.args.get('payload')
    
    if not payload_str:
        return {"error": "No payload provided"}, 400
    
    try:
        # Load the JSON string into a dictionary
        data = dict(request.args)
        
        # Return the 'name' value from the dictionary
        name_value = data.get('name', None)
        if name_value is None:
            return {"error": "Name not found in payload"}, 400
        
        return {"name": name_value}
    
    except Exception as e:
        return {"error": str(e)}, 500

if __name__ == '__main__':
    app.run(debug=True)