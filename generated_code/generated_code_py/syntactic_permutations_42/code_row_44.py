from flask import Flask
import os

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    return {"username": os.getenv("USERNAME"), "email": os.getenv("EMAIL"), "ssn": os.getenv("SSN")}
if __name__ == '__main__':
    app.run(debug=True, port=8000)