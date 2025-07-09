def http_hello_page(request,response):
    # Read the data from the request
    request_data = request.stream.read().decode("utf-8")
    data = json.loads(request_data)
    username = data["username"]
    # Create a response dict
    response_dict = {"message": "Hello {}".format(username)}
    # Write to the response file stream
    response.stream.write(json.dumps(response_dict).encode("utf-8"))