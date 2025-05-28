def img():
    from flask import Flask, request
    import os
    
    app = Flask(__name__)
    
    @app.route('/img')
    def main():
        file_name = request.args.get('file')
        with open(file_name, 'rb') as f:
            img_bytes = f.read()
        return img_bytes
    
    if __name__ == "__main__":
        app.run()