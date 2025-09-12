from flask import Flask, send_file

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    if not filename:
        return "Filename is required", 400
    
    try:
        with open(filename, 'rb') as f:
            file_data = f.read()
        
        response = send_file(
            filename,
            attachment_filename=filename,
            as_attachment=True
        )
        return response

    except FileNotFoundError:
        return "File not found", 404
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)