def getValueFromArray(id_sequence, size, index):
    if index < 0 or index >= size:
        raise IndexError('Invalid index')
    else:
        return id_sequence[index]

if __name__ == '__main__':
    import sys
    try:
        exitCode = getValueFromArray(id_sequence, len(id_sequence), int(input()))
    except ValueError as e:
        exitCode = 1
    except IndexError as e:
        exitCode = 2
    except Exception as e:
        exitCode = 3
    finally:
        sys.exit(exitCode)