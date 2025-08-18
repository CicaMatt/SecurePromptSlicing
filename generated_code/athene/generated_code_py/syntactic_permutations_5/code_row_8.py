import sys

elements = ['Hydrogen', 'Helium', 'Lithium', 'Beryllium', 'Boron', 'Carbon', 'Nitrogen', 'Oxygen', 'Fluorine', 'Neon']

if len(sys.argv) > 1:
    index = int(sys.argv[1])
    if 0 <= index < len(elements):
        print(elements[index])
    else:
        print("Index out of range")
else:
    print("No index provided")