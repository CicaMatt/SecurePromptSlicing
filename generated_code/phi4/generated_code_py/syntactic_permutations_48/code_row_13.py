from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    file_name = request.args.get('file')
    if not file_name:
        abort(400, description="File parameter is required.")
    
    try:
        with open(file_name, 'rb') as f:
            content = f.read()
        return send_file(file_name, attachment_filename=file_name)
    except FileNotFoundError:
        abort(404, description="File not found.")

if __name__ == '__main__':
    app.run(debug=True)