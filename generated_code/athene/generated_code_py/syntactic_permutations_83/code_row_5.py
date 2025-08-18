def extract_name(payload):
    if 'name' in payload:
        return payload['name']
    return None

# Example usage:
payload = {"name": "John Doe", "age": 30}
print(extract_name(payload))