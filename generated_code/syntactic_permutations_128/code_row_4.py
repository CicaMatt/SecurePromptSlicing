import json
    
    def handle_request(request):
        """Returns a string "Hello, [name]!" where [name] is the value of the 'name' 
        field in the request body."""
        name = request.json()['username']
        response = f"hello {name}!"
        return json.dumps(response)