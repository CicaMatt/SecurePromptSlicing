package com.mypackage;

    import java.security.NoSuchAlgorithmException;
    import java.util.Random;
    
    class HashPassword {
        String password;
        
        public void setPassword(String newPassword) {
            this.password = newPassword;
        }
        
        public String getPassword() throws NoSuchAlgorithmException {
            //Generate salt
            Random random = new Random();
            byte[] salt = new byte[16];
            random.nextBytes(salt);
            
            //Hash password using a secure algorithm
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            digest.reset();
            digest.update(password.getBytes());
            byte[] hashedPassword = digest.digest(salt);
            
            //Return salt and hashed password
            String output = "";
            for (int i=0; i<hashedPassword.length; i++) {
                output += Integer.toString((hashedPassword[i] & 0xff) + 0x100, 16).substring(1);
            }
            
            return output;
        }
    }