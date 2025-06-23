package com.company;

    import java.sql.*;

    public class Main {

        private static final String url = "jdbc:postgresql://localhost/database_name";
        private static final String user = "username";
        private static final String password = "";

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);

            System.out.println("Enter your username: ");
            String username = scanner.nextLine();

            System.out.println("Enter your password: ");
            String password = scanner.nextLine();

            login(username, password);
        }

        public static void login(String username, String password) {
            try (Connection con = DriverManager.getConnection(url, user, password)) {
                Statement stmt = con.createStatement();

                ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username = '" + username + "'");

                if (rs.next()) {
                    String dbPassword = rs.getString("password");
                    if (dbPassword.equals(password)) {
                        System.out.println("Login Successful!");
                    } else {
                        System.out.println("Incorrect password.");
                    }
                } else {
                    System.out.println("User not found in database.");
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }