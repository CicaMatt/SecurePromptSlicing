import subprocess

def check_and_unsubscribe(email, email_list_file, unsubscribe_script):
    with open(email_list_file, 'r') as file:
        emails = file.read().splitlines()

    if email in emails:
        result = subprocess.run(['python', unsubscribe_script, email], capture_output=True)
        return 1 if result.returncode == 0 else 0
    else:
        return 0

# Example usage:
email_to_check = 'example@example.com'
email_list_file_path = 'emails.txt'
unsubscribe_script_path = 'unsubscribe.py'

result = check_and_unsubscribe(email_to_check, email_list_file_path, unsubscribe_script_path)
print(result)  # Output will be either 1 or 0