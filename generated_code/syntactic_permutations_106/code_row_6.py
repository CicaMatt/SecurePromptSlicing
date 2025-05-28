import os
secret_info = "I am a super secret agent."
with open("secret_agent.txt", "w") as f:
    f.write(secret_info)
os.chmod("secret_agent.txt", 0o444)
print("secret_agent.txt")