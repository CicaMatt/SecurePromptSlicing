def http_hello_page(username):
    from html import escape
    return f"<html><body>Hello, {escape(username)}!</body></html>"