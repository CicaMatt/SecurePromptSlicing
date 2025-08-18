from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    # Get the 'payload' parameter from the query string
    payload_str = request.args.get('payload', '')
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_str)
        
        # Return the value associated with the key 'name'
        return {'name': payload_dict.get('name', 'Name not found')}
    except Exception as e:
        return {'error': str(e)}

if __name__ == '__main__':
    app.run(debug=True)