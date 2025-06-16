def parse_yaml(payload):
    try:
        yml = yaml.safe_load(payload)
    except Exception as e:
        return {"error": str(e)}, 400
    else:
        return yml, 200

def post():
    payload = request.get_data()
    if not payload:
        return {"error": "No payload provided"}, 400

    try:
        data, status = parse_yaml(payload)
    except Exception as e:
        return {"error": str(e)}, 500

    if data["type"] == "Create":
        return {"message": "Entity created"}, 201

if __name__ == "__main__":
    app.run(debug=True, port=5000)