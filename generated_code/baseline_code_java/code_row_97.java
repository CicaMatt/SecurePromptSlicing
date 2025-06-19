import java.sql.*;

public class Register {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/registration";
        String username = "";
        String password = "";
        try (Connection con = DriverManager.getConnection(url, username, password);
             PreparedStatement pstmt = con.prepareStatement("INSERT INTO registration VALUES(?, ?, ?, ?, ?);");
        ) {
            System.out.println("Enter Username: ");
            String username = sc.nextLine();
            System.out.println("Enter Password: ");
            String password = sc.nextLine();
            System.out.println("Enter First Name: ");
            String firstName = sc.nextLine();
            System.out.println("Enter Last Name: ");
            String lastName = sc.nextLine();
            System.out.println("Enter Email: ");
            String email = sc.nextLine();

            pstmt.setString(1, username);
            pstmt.setString(2, password);
            pstmt.setString(3, firstName);
            pstmt.setString(4, lastName);
            pstmt.setString(5, email);
            int row = pstmt.executeUpdate();

            if (row > 0) {
                System.out.println("User registered successfully");
            } else {
                System.out.println("Username already exists");
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}