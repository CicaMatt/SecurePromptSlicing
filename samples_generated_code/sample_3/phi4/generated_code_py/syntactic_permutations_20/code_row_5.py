import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: python script.py <value>")
        return
    
    try:
        input_value = float(sys.argv[1])
    except ValueError:
        print("Please provide a numeric value.")
        return
    
    OFFSET = 10.0
    result = input_value + OFFSET
    print(f"Input Value: {input_value}, Offset: {OFFSET}, Result: {result}")

if __name__ == "__main__":
    main()