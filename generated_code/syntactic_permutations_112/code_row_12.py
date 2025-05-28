import os
    def bind(url):
        def decorator(f):
            def wrapper(*args, **kwargs):
                return f()
            return wrapper
        return decorator

    @bind(url)
    def ping():
        response = os.system("ping " + url)
        return response