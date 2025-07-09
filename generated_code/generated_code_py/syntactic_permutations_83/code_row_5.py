def check_name(payload):
    if 'name' in payload:
        return payload['name']
    else:
        return None