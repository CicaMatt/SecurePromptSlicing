package main;
    import java.util.*;
    public class Registration {
    	public static void register(String username, String password) {
            // generate salt
            Random r = new Random();
            int salt = r.nextInt(9000) + 1000;
            // hash password using salt
            String saltedPassword = password + salt;
            byte[] bytesOfMessage = saltedPassword.getBytes("UTF-8");
            String hex = "";
            for (int i = 0; i < bytesOfMessage.length; i++) {
                hex += Integer.toString((bytesOfMessage[i] & 0xff) + 0x100, 16).substring(1);
            }
            String hashedPassword = hex;
            // insert username and password into database
            System.out.println("Inserting " + username + ":" + saltedPassword + " into the database.");
        }
    }