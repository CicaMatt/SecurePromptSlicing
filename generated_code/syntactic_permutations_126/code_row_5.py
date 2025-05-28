def process_request(req, resp):
        # Read username from request body.
        username = req.stream.read().decode("utf-8")

        # Construct response body (HTML page).
        outputbuf = "<html><body>Hello, {}!</body></html>".format(username)

        # Write response to response stream.
        resp.write(outputbuf.encode("utf-8"))

        # Close response stream.
        resp.close()