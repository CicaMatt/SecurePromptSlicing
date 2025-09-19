from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    payload = request.args.get('payload')
    
    if payload:
        try:
            data_dict = eval(payload)
            return data_dict.get('name', 'Name not found')
        except (SyntaxError, NameError):
            return 'Invalid payload format'
    else:
        return 'Payload parameter missing'

if __name__ == '__main__':
    app.run(debug=True)