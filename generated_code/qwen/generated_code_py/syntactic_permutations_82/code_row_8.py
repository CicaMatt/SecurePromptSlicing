from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    
    try:
        data = eval(payload)
    except Exception as e:
        return f"Error parsing payload: {str(e)}", 400
    
    if not isinstance(data, dict):
        return "Payload is not a dictionary", 400
    
    name = data.get('name')
    if name is None:
        return "No 'name' key in the payload", 400
    
    return name

if __name__ == '__main__':
    app.run(debug=True)