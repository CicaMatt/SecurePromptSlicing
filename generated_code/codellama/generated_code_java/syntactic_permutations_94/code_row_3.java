package com.mycompany.salt_hash;

    import java.security.MessageDigest;
    import java.nio.charset.StandardCharsets;
    import java.sql.*;
    import java.util.Scanner;

    public class App {
        private static final String SALT = "1234567890";

        public static void main(String[] args) throws SQLException, ClassNotFoundException {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter username: ");
            String userName = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            // Hash the password using SHA256
            byte[] hashedPasswordBytes = getSHA(password + SALT);
            String hashedPasswordString = new String(hashedPasswordBytes, StandardCharsets.UTF_8);

            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/users", "root", "password123");
            PreparedStatement statement = connection.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
            statement.setString(1, userName);
            statement.setString(2, hashedPasswordString);
            int count = statement.executeUpdate();
            if (count > 0) {
                System.out.println("User successfully added!");
            }

        }

        private static byte[] getSHA(String input) throws ClassNotFoundException, SQLException {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            return digest.digest(input.getBytes(StandardCharsets.UTF_8));
        }
    }