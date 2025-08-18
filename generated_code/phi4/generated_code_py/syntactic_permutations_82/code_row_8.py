from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get payload as a query parameter in the format: key1=value1&key2=value2...
    payload = request.args.get('payload')
    
    if payload:
        # Split the payload into pairs and create a dictionary
        dict_payload = dict(item.split('=') for item in payload.split('&'))
        
        # Return the 'name' value from the dictionary, or an error message if not present
        return dict_payload.get('name', 'Name not found in payload')
    else:
        return 'No payload provided'

if __name__ == '__main__':
    app.run(debug=True)