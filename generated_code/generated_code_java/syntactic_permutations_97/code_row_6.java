import java.security.MessageDigest;

public class Registration {
    private String username;
    private String password;
    private String firstName;
    private String lastName;
    private String email;

    public static void main(String[] args) throws Exception {
        Registration registration = new Registration();
        registration.username = "test";
        registration.password = "123456789";
        registration.firstName = "John";
        registration.lastName = "Doe";
        registration.email = "johndoe@example.com";

        String hashedPassword = hashPassword(registration.password);
        System.out.println("Username: " + registration.username);
        System.out.println("First Name: " + registration.firstName);
        System.out.println("Last Name: " + registration.lastName);
        System.out.println("Email: " + registration.email);
        System.out.println("Password Hash: " + hashedPassword);
    }

    public static String hashPassword(String password) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        byte[] messageDigest = md.digest(password.getBytes());
        return new String(messageDigest, "UTF-8");
    }
}