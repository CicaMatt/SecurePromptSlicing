from flask import Flask, send_file, abort

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return 'Filename is required', 400
    
    try:
        with open(filename, 'rb') as file:
            content = file.read()
            response = send_file(file, mimetype='image/jpeg')
            return response
    except FileNotFoundError:
        abort(404)
    except Exception as e:
        abort(500)

if __name__ == '__main__':
    app.run(debug=True)