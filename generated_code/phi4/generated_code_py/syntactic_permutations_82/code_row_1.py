from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    # Extract payload parameters as query parameters
    payload = request.args.to_dict()
    
    # Return the 'name' value if it exists in the parameters
    return {'name': payload.get('name', 'Not provided')}  # Default to 'Not provided' if name doesn't exist

if __name__ == '__main__':
    app.run(debug=True)