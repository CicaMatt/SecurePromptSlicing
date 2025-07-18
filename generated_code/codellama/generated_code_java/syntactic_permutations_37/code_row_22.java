import java.io.*;

public class Login {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        String username;
        System.out.print("Enter username: ");
        username = reader.readLine();

        String password;
        System.out.print("Enter password: ");
        password = reader.readLine();

        try {
            // Open and connect to database
            Connection conn = DriverManager.getConnection(DB_URL, USERNAME, PASSWORD);

            // Create a statement
            Statement stmt = conn.createStatement();

            // Execute SQL query
            ResultSet rs = stmt.executeQuery("SELECT * FROM Users WHERE username='" + username + "' AND password='" + password + "'");

            // Print results
            while (rs.next()) {
                System.out.println(username);
                System.out.println(password);
            }

            // Close statement and connection
            stmt.close();
            conn.close();
        } catch (SQLException e) {
            throw new IOException("Error connecting to database", e);
        }
    }
}