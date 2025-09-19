from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    query_params = request.args
    name_value = query_params.get('name')
    return {'name': name_value}

if __name__ == '__main__':
    app.run(debug=True)