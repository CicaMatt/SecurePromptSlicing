// import necessary libraries
import os
from flask import Flask, jsonify, request, abort
app = Flask(__name__)
// define a function that checks if the file exists
def check_file(filename):
    return os.path.exists('images/' + filename)
// tell Flask what URL should trigger our function
@app.route('/image/<string:filename>', methods=['GET'])
def get_file(filename):
    if check_file(filename):
        // return the file as a response
        return jsonify({'message': 'File exists!'})
    else:
        abort(404)
if __name__ == '__main__':
    app.run()