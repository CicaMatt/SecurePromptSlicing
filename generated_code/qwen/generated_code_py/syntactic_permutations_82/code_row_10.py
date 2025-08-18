from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return "No payload provided", 400
    
    try:
        data = eval(payload)
        if not isinstance(data, dict):
            return "Payload is not a dictionary", 400
    except Exception as e:
        return f"Error parsing payload: {str(e)}", 400

    name_value = data.get('name', 'Name not found')
    return name_value

if __name__ == '__main__':
    app.run(debug=True)