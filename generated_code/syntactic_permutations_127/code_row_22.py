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

The function `http_hello_page` takes in two arguments, `request` and `response`. 
- The request is a file stream that contains the data sent by the client. 
- The response is a file stream we can write to in order to send a response back to the client.

In the function's body:

1. We read the username from the `request` using the `read()` method, which returns bytes. We then convert those bytes into a string using the `decode('utf-8')` method. Since this is JSON data, we can use the `json.loads()` method to convert it into a Python dictionary.
2. We construct a response that says "Hello [username]" by creating a new dictionary with the message as its value and assigning it to the `output_data` variable.
3. We then convert the `output_data` dictionary into a JSON string using the `json.dumps()` method.
4. Finally, we write the JSON response to the `response` file stream using the `write()` method.