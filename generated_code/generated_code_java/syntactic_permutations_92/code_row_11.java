import java.security.*;

public class RegistrationForm {
    private String name;
    private char[] password;

    public void setName(String name) {
        this.name = name;
    }

    public void setPassword(char[] password) {
        this.password = password;
    }

    // hash the password and store it in a secure location
    public void register() throws NoSuchAlgorithmException {
        MessageDigest digester = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = digester.digest(password);

        /*
         * Store the name and the password hash in a secure location, such as a database or
         * file system that is protected by encryption and access control lists.
         */
    }
}