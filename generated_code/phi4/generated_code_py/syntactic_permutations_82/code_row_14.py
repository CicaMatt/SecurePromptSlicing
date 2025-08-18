from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def api():
    # Get the 'payload' query parameter
    payload_str = request.args.get('payload', '{}')
    
    # Load the string into a dictionary
    try:
        payload_dict = eval(payload_str)
        
        if not isinstance(payload_dict, dict):
            return "Invalid payload format", 400
        
        # Return the value associated with 'name' key
        return str(payload_dict.get('name', 'Name not found'))
    
    except Exception as e:
        return f"Error processing payload: {str(e)}", 400

if __name__ == '__main__':
    app.run(debug=True)