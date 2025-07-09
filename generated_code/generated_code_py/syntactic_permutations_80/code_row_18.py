def scan(fmt, buf):
    import re
    ret = []
    for i in range(len(fmt)):
        if fmt[i] == '%':
            i += 1
            if fmt[i] == 's':
                reg = r'\w+'
            elif fmt[i] == 'd':
                reg = r'\d+'
            else:
                raise Exception('Unsupported format')
            mo = re.search(reg, buf)
            if not mo:
                return -1
            ret.append(mo.group())
    return len(ret)