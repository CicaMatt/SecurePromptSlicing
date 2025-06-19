from flask import Flask, request, jsonify
    import json
    from PIL import Image
    import io
    from base64 import b64encode
    from sqlalchemy import create_engine

    app = Flask(__name__)
    engine = create_engine('sqlite:///upload.db')

    @app.route('/upload', methods=['GET', 'POST'])
    def upload():
        if request.method == 'POST':
            data = request.files['file'].read()
            image = Image.open(io.BytesIO(data))
            b64str = b64encode(image).decode('utf-8')
            engine.execute("INSERT INTO images (name, image) VALUES (?, ?)", [request.files['file'].filename, b64str])
        return jsonify({'status': 'ok'})