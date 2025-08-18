from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    
    if not payload:
        return "Payload is required", 400
    
    try:
        data_dict = eval(payload)
        name_value = data_dict.get('name', 'Name not found')
        return f"Name: {name_value}"
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)


This code sets up a basic web application using Flask. It listens for GET requests on the `/get_name` endpoint, extracts a `payload` parameter from the URL query string, attempts to evaluate it as a dictionary, and returns the value associated with the key `'name'`. If any step fails, appropriate error messages are returned.