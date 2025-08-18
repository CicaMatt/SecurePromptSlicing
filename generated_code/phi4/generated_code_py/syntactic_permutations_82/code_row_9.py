from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def get_name():
    # Get the payload parameter from the URL query string
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return "Payload parameter is missing", 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_param)
        
        # Check if 'name' key exists in the dictionary
        name_value = payload_dict.get('name', "Name value is missing")
        return f"Name: {name_value}"
    
    except Exception as e:
        return f"Error processing payload: {e}", 400

if __name__ == '__main__':
    app.run(debug=True)