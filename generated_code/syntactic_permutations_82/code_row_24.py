def get_dict_from_payload(payload):
    dict = {}
    for item in payload:
        key, value = item.split("=")
        dict[key] = value
    return dict

@app.route("/api")
def api():
    payload = request.args.get("payload")
    dict = get_dict_from_payload(payload)
    # do something with the dictionary
    return "Success"