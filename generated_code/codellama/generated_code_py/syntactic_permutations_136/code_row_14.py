def check_mod():
    mod = request.args.get('mod')
    if int(mod) % 2 == 0:
        return 'true'
    else:
        return 'false'