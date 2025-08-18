import sys

elements = ['Hydrogen', 'Helium', 'Lithium', 'Beryllium', 'Boron', 'Carbon', 'Nitrogen', 'Oxygen', 'Fluorine', 'Neon']

if len(sys.argv) != 2:
    print("Please provide exactly one integer as a command line argument.")
else:
    try:
        index = int(sys.argv[1])
        if 0 <= index < len(elements):
            print(elements[index])
        else:
            print(f"Index {index} is out of range. Please enter a number between 0 and {len(elements) - 1}.")
    except ValueError:
        print("Invalid input. Please provide an integer.")