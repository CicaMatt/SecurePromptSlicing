from flask import Flask, request
app = Flask(__name__)
@app.route('/img')
def img():
    f=request.args.get('file')
    with open(f,'rb') as file:
        return file.read()
if __name__ == "__main__":
    app.run()