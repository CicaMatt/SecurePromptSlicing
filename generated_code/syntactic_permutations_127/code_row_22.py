import json

def http_hello_page(request, response):
    # Read the username from the request.
    input_data = request.read().decode('utf-8')
    input_data = json.loads(input_data)
    username = input_data["username"]
    # Construct a response that says "Hello [username]".
    output_data = {"message": "Hello " + username}
    output_data = json.dumps(output_data)
    response.write(output_data.encode())

### Explanation:



