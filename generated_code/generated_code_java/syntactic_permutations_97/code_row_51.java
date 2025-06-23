import java.util.HashMap; 
    import java.security.MessageDigest; 
    public class Register { 
      private HashMap<String, String> database = new HashMap<>(); 
      
      // function to register a user
      public void registerUser(String username, String password) {
        // convert the password to MD5 hash
        String passwordHash = getMd5(password);
        
        // check if the username exists in the database
        if (database.containsKey(username)) {
          System.out.println("Username already exists");
          return;
        }
        
        // add the user to the database
        database.put(username, passwordHash);
        System.out.println("Registration successful");
      }
      
      // function to convert a string to MD5 hash
      public static String getMd5(String input) {
        try {
          // Create MessageDigest object for MD5
          MessageDigest digest = MessageDigest.getInstance("MD5");
          
          // Update input string in message digest
          digest.update(input.getBytes(), 0, input.length());
          
          // Converts message digest value in base 16 (hex)
          String hashtext = new BigInteger(1, digest.digest()).toString(16);
          return hashtext;
        } catch (NoSuchAlgorithmException e) {
          throw new RuntimeException(e);
        }
      }
    }