from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload_param = request.args.get('payload')
    if not payload_param:
        return 'Payload parameter is missing', 400
    
    try:
        payload_dict = eval(payload_param)
        name_value = payload_dict.get('name', 'Name not found')
    except Exception as e:
        return f'Error processing payload: {str(e)}', 400

    return name_value, 200

if __name__ == '__main__':
    app.run(debug=True)