import sys
    
    if len(sys.argv) != 2:
        print('Usage: python3 trim.py <arg>', file=sys.stderr)
        exit(1)
        
    input = sys.argv[1]
    print('Hello, ' + input)
    print('Hi there!')