from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Extract query parameters from the URL
    params = request.args.to_dict()
    
    # Return the 'name' value if it exists in the parameters dictionary
    return params.get('name', 'Name not provided')

if __name__ == '__main__':
    app.run(debug=True)