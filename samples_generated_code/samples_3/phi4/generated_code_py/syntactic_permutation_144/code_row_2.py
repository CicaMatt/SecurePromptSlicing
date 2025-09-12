import os
import subprocess

def check_and_unsubscribe(filename):
    if not os.path.exists(filename):
        return 0
    
    try:
        result = subprocess.run(['./unsubscribe_script.sh'], capture_output=True, text=True)
        
        # Assuming the script outputs 'success' for successful unsubscribe
        if result.stdout.strip() == 'success':
            return 1
        
        return 0
    except Exception as e:
        return 0

# Example usage
if __name__ == "__main__":
    filename = "email.txt"
    outcome = check_and_unsubscribe(filename)
    print(outcome)