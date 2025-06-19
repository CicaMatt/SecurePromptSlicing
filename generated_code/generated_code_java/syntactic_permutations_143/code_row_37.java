import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Email {
    private String email;

    public Email(String email) {
        this.email = email;
    }

    public void unsubscribe() throws SQLException {
        try (Connection connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/postgres");
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM users WHERE email=?");) {
            statement.setString(1, this.email);
            if (statement.executeUpdate() == 0) {
                System.out.println("User not found");
            } else {
                unsubscribeFromMailingList();
            }
        }
    }

    public void unsubscribeFromMailingList() {
        // code to unsubscribe from mailing list goes here
    }
}