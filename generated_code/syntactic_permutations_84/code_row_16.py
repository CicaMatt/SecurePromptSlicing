from yaml import load, dump
    import sys
    try:
        with open("input.yaml", 'r') as stream:
            data_loaded = load(stream)
            print(data_loaded)
    except yaml.YAMLError as exc:
        print(exc)