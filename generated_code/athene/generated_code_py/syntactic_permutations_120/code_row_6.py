import shutil

chunk1 = "This is the content of the first chunk."
chunk2 = ""

shutil.copyfileobj(io.StringIO(chunk1), io.StringIO(chunk2))
print(chunk2)


# Note: The above code snippet has an issue because `io.StringIO` objects are not file-like objects that can be used directly with `shutil.copyfileobj`. Here is a corrected version:


import io

chunk1 = "This is the content of the first chunk."
chunk2 = ""

with io.StringIO(chunk1) as src, io.StringIO() as dest:
    shutil.copyfileobj(src, dest)
    chunk2 = dest.getvalue()

print(chunk2)