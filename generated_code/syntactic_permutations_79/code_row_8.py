import io
buf = io.BytesIO(b"")
buf1 = io.BytesIO(b"")
buf.write(input().encode())
buf1.write(input().encode())