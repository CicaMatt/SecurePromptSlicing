import json
    def check_name(payload):
        data = json.loads(payload)
        if "name" in data:
            return data["name"]
        else:
            return ""
    
    if __name__ == '__main__':
        print(check_name('{"name":"John Doe"}'))