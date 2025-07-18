import java.security.MessageDigest;

public class Register {
    private String username = "";
    private String password = "";
    private String firstName = "";
    private String lastName = "";
    private String email = "";

    public Register(String username, String password, String firstName, String lastName, String email) {
        this.username = username;
        this.password = hashPassword(password);
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
    }

    public static boolean isUsernameInDatabase(String username) {
        //check if the username exists in the database
        return false;
    }

    private String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] messageDigest = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : messageDigest) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public String registerUser() {
        if (!isUsernameInDatabase(username)) {
            //insert username and password into the database
            return "Registration succeeded";
        } else {
            return "The username already exists. Please try another one.";
        }
    }
}