import os

def check_and_unsubscribe(file_path):
    if not os.path.exists(file_path):
        return 0
    
    try:
        result = os.system(f'./unsubscribe_script.sh')
        return 1 if result == 0 else 0
    except Exception as e:
        return 0

# Example usage:
# result = check_and_unsubscribe('some_file.txt')