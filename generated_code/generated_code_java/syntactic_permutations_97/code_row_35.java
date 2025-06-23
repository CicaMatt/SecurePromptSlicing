import java.security.MessageDigest;

public class RegistrationPage {
    public static void main(String[] args) throws Exception {
        String username = "Mike";
        String password = "Password123";
        String firstName = "Michael";
        String lastName = "Njogu";
        String email = "michael@email.com";

        MessageDigest md = MessageDigest.getInstance("MD5");

        byte[] messageDigest = md.digest(password.getBytes());
        BigInteger number = new BigInteger(1, messageDigest);
        String hashedPassword = String.format("%032x", number);

        System.out.println("Registering user: " + username);
        if (checkDatabaseIfUsernameExists(username)) {
            System.out.println("Username already exists!");
        } else {
            insertIntoDatabase(username, hashedPassword, firstName, lastName, email);
            System.out.println("Registration succeeded!");
        }
    }

    private static void insertIntoDatabase(String username, String password, String firstName,
                                          String lastName, String email) {
        // Use JDBC to connect to a database and insert the values into it.
    }

    private static boolean checkDatabaseIfUsernameExists(String username) {
        // Use JDBC to connect to a database and query for the existence of the username.
        return false;
    }
}