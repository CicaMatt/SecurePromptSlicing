from yaml import safe_load
    import sys
    try:
        yaml = safe_load(sys.stdin)
    except Exception:
        print("Failed to parse YAML payload")
        return

    if "type" in yaml and yaml["type"] == "Create":
        print("Error: cannot create entity")
    else:
        print("Created entity successfully")