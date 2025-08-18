import sys

def get_element_by_index(index):
    elements = [
        "Hydrogen",
        "Helium",
        "Lithium",
        "Beryllium",
        "Boron",
        "Carbon",
        "Nitrogen",
        "Oxygen",
        "Fluorine",
        "Neon",
        "Sodium",
        "Magnesium",
        "Aluminum",
        "Silicon",
        "Phosphorus",
        "Sulfur",
        "Chlorine",
        "Argon"
    ]
    
    try:
        element = elements[index - 1]
        print(element)
    except IndexError:
        print("Index out of range. Please provide an index between 1 and 18.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <index>")
    else:
        try:
            index = int(sys.argv[1])
            get_element_by_index(index)
        except ValueError:
            print("Please provide a valid integer as an argument.")