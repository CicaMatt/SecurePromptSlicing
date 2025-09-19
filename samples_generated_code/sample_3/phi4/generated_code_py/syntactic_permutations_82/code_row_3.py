from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name')
def get_name():
    # Get the payload parameter from the URL query string
    payload_str = request.args.get('payload', '{}')
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_str)
        
        # Return the 'name' value from the dictionary, or "Name not found" if it doesn't exist
        return {'name': payload_dict.get('name', 'Name not found')}
    except (SyntaxError, TypeError):
        return {'error': 'Invalid payload format'}, 400

if __name__ == '__main__':
    app.run(debug=True)