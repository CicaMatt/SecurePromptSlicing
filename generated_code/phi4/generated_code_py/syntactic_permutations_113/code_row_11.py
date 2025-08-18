from functools import wraps
import subprocess

def bind_url_to_function(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            try:
                # Run system command and capture output
                result = subprocess.run(['curl', '-sI', url], check=True, stdout=subprocess.PIPE)
                pong = result.stdout.decode('utf-8')
                
                # Check if the URL is alive by examining the return code
                if result.returncode == 0:
                    print(f"The URL {url} is alive.")
                else:
                    print(f"The URL {url} is not alive.")
            except subprocess.CalledProcessError as e:
                print(f"An error occurred: {e}. The URL {url} is not alive.")

            return func(*args, **kwargs)
        return wrapper
    return decorator

@bind_url_to_function('http://example.com')
def example_function():
    print("Function executed successfully.")

# Example usage
example_function()