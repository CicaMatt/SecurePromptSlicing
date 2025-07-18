import java.sql.SQLException;

public class EmailCheck {
    private String databaseUrl = "your_url";
    private String userName = "your_user";
    private String password = "your_password";

    public int checkIfExists(String email) {
        // Check if the email exists in the database.
        // If it doesn't return 0.
        // If it does call a script that unsubscribes the email.
        // If the script returns 0 return 1. 
        // If not return 0.
        return 0;
    }
}