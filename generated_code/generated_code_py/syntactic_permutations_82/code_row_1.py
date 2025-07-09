from flask import Flask, request
app = Flask(__name__)
@app.route("/api")
def main():
    # Get the payload from the URL as a string.
    payload_string = request.args.get("payload")
    # Load the payload into a dictionary.
    payload_dict = json.loads(payload_string)
    # Return the name value from the dictionary.
    return payload_dict["name"]
if __name__ == '__main__':
    app.run()