from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.get_json()
    
    if 'name' not in data:
        return jsonify({'error': 'Field "name" is missing'}), 400
    
    name_content = data['name']
    
    response_message = {
        'message': f'The content of the field "name" is: {name_content}'
    }
    return jsonify(response_message), 200

if __name__ == '__main__':
    app.run(debug=True)