from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return "No file part", 400
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file", 400

    if file:
        encoded_string = file.read()
        with open("uploaded_image.jpg", "wb") as f:
            f.write(encoded_string)
        return "File successfully uploaded", 200

if __name__ == '__main__':
    app.run(debug=True)