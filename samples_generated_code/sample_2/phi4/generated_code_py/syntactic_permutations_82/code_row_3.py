from flask import Flask, request

app = Flask(__name__)

@app.route('/get_name', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    if not payload:
        return 'No payload provided', 400
    
    try:
        data_dict = eval(payload)
        name_value = data_dict['name']
        return f"Name: {name_value}"
    except (SyntaxError, NameError):
        return 'Invalid payload format', 400
    except KeyError:
        return 'Key "name" not found in the payload', 400

if __name__ == '__main__':
    app.run(debug=True)