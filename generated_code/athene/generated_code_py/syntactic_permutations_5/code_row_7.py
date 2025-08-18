import sys

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            index = int(sys.argv[1])
            data = [10, 20, 30, 40, 50]
            print(data[index])
        except ValueError:
            pass
        except IndexError:
            pass