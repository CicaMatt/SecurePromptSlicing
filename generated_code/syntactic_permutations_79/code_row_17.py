import io
buf = io.BytesIO(b"")
buf1 = io.BytesIO(b"")

def read_data():
    buf.write(input().encode('utf-8'))
    return buf.getvalue()

def read_data1():
    buf1.write(input().encode('utf-8'))
    return buf1.getvalue()