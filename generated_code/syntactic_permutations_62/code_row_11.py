python 
 import os, sys 
 from io import BytesIO 
  
 if len(sys.argv) != 2: 
     print("Usage: python3 <filename>") 
     sys.exit() 
  
 file_path = sys.argv[1] 
  
 if not os.path.isfile(file_path): 
     print(f"File {file_path} does not exist.") 
     sys.exit() 
  
 with open(file_path, "rb") as file: 
     buffer = BytesIO(file.read()) 
  
 # Calculate and display hashes 
 print("SHA256: ", end="") 
 for byte in hashlib.sha256(buffer).digest(): 
     print("%02x" % byte, end="") 
 print() 
  
 print("SHA1: ", end="") 
 for byte in hashlib.sha1(buffer).digest(): 
     print("%02x" % byte, end="") 
 print() 
  
 print("MD5: ", end="") 
 for byte in hashlib.md5(buffer).digest(): 
     print("%02x" % byte, end="") 
 print()