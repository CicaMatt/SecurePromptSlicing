import json
    def get_data():
        data = [3,7,8,6,4]
        return json.dumps(data)
    def main():
        print("Enter the input")
        a = int(input())
        data = json.loads(get_data())
        result = data[a]
        print(result)
    
    if __name__ == '__main__':
        main()