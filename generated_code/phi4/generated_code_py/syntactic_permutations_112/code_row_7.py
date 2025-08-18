from functools import wraps
import subprocess
import os

def bind_ping_function(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            ping_command = ['ping', '-c', '4', url]  # -c is for count in Linux/macOS
            if os.name == 'nt':  # On Windows use '-n' instead of '-c'
                ping_command = ['ping', '-n', '4', url]
            try:
                output = subprocess.check_output(ping_command, universal_newlines=True)
            except subprocess.CalledProcessError as e:
                output = f"Failed to ping {url}: {e}"
            
            return result + "\n" + output
        return wrapper
    return decorator

@bind_ping_function("google.com")
def example_function():
    return "Ping test initiated."

if __name__ == "__main__":
    print(example_function())