from flask import Flask, request

app = Flask(__name__)

@app.route('/check_name', methods=['POST'])
def check_name():
    data = request.json
    if 'name' in data:
        return data['name']
    return "Field 'name' not found", 400

if __name__ == '__main__':
    app.run(debug=True)