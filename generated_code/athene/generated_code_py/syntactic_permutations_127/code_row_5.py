import os

def handle_request(request, response_file):
    username = request.get('username', 'Guest')
    response = f"Hello {username}\n"
    with open(response_file, 'w') as f:
        f.write(response)

# Example usage
request = {'username': 'JohnDoe'}
response_file = 'response.txt'
handle_request(request, response_file)