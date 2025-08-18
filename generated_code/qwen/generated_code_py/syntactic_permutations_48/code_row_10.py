from flask import Flask, request, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    try:
        return send_file(filename, mimetype='image/*', as_attachment=True)
    except FileNotFoundError:
        return "File not found", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)