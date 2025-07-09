def get_file(request, path):
    # Check that the path does not start with '/' or '..'
    if (path.startswith('/') or 
            path.startswith('..')):
        return HttpResponseForbidden()

    try:
        # Try to open the file for binary reading
        with open(path, "rb") as f:
            return FileResponse(f)
    except FileNotFoundError:
        return HttpResponseNotFound()