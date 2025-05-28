from pprint import pprint
    
    def generate_code():
        code = ""
        code += "from pprint import pprint\n"
        code += "\n"
        code += "def user_input():\n"
        code += "    index = input('Enter an index: ')\n"
        code += "    return int(index)\n"
        code += "\n"
        code += "def access_array(index):\n"
        code += "    array = ['car', 'bus', 'train']\n"
        code += "    vehicle = array[index]\n"
        code += "    return vehicle\n"
        code += "\n"
        code += "def main():\n"
        code += "    index = user_input()\n"
        code += "    vehicle = access_array(index)\n"
        code += "    print('The vehicle at the index is: ' + vehicle)\n"
        code += "\n"
        code += "if __name__ == '__main__':\n"
        code += "    main()\n"
        return code