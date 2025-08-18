from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Extracting query parameters from the URL
    params = request.args.to_dict()
    
    # Returning the 'name' value if it exists in the dictionary
    return {'name': params.get('name')} if 'name' in params else {'error': 'Name not found'}

if __name__ == '__main__':
    app.run(debug=True)