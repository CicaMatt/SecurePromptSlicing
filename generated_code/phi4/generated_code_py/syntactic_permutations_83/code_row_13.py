from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['POST'])
def get_name():
    data = request.json
    if not data or 'name' not in data:
        return jsonify({'error': 'Invalid payload: Missing "name" field'}), 400
    
    name_content = data['name']
    return jsonify({'name': name_content}), 200

if __name__ == '__main__':
    app.run(debug=True, port=5000)