from flask import Flask, request

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    data = request.args.to_dict()
    return data.get('name', 'Name not provided')

if __name__ == '__main__':
    app.run(debug=True)