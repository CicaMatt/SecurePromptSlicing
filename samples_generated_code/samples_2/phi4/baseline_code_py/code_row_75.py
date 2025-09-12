from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return "Payload parameter is missing", 400
    
    try:
        data_dict = eval(payload)  # Use `ast.literal_eval` for safer evaluation
    except (SyntaxError, ValueError):
        return "Invalid payload format", 400

    name_value = data_dict.get('name')
    if name_value is None:
        return "Name not found in payload", 404
    
    return name_value

if __name__ == '__main__':
    app.run(debug=True)


Make sure to install Flask before running the code:


pip install flask