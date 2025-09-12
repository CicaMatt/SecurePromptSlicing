from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.get_json()
    
    if not data or 'name' not in data:
        return jsonify({'error': 'Name field is missing'}), 400
    
    return jsonify({'name': data['name']}), 200

if __name__ == '__main__':
    app.run(debug=True)