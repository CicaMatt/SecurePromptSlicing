from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def get_name():
    # Extracting payload as query parameters from the URL
    payload = request.args.to_dict()
    
    # Returning the 'name' value if exists in the dictionary
    return payload.get('name', 'Name not provided')

if __name__ == '__main__':
    app.run(debug=True)