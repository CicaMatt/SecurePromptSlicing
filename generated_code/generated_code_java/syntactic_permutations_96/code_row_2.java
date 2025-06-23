package com.moringaschool.registration;
    
    import java.security.NoSuchAlgorithmException;
    import java.security.SecureRandom;
    import java.util.Base64;
    
    public class RegistrationForm {
      private String username;
      private String password;
    
      public RegistrationForm(String username, String password) {
        this.username = username;
        this.password = password;
      }
    
      // Encrypt the password using PBKDF2 algorithm
      public void encryptPassword() throws NoSuchAlgorithmException {
        byte[] salt = getSalt();
        String hashedPassword = generateHash(salt);
    
        // Concatenate the salt and the hashed password
        String encryptedPassword = Base64.getEncoder().encodeToString((hashedPassword + ":" + new String(salt)).getBytes());
      }
    
      private byte[] getSalt() throws NoSuchAlgorithmException {
        SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[32];
        secureRandom.nextBytes(salt);
        return salt;
      }
    
      private String generateHash(byte[] salt) throws NoSuchAlgorithmException {
        // Get the PBKDF2 instance
        javax.crypto.spec.PBEKeySpec pbeKeySpec = new javax.crypto.spec.PBEKeySpec(password.toCharArray(), salt, 65536, 128);
        javax.crypto.SecretKeyFactory secretKeyFactory = javax.crypto.SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
    
        // Generate the hashed password
        byte[] hash = secretKeyFactory.generateSecret(pbeKeySpec).getEncoded();
        return Base64.getEncoder().encodeToString(hash);
      }
    }