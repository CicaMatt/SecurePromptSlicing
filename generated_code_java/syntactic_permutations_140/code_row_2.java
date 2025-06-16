import java.sql.*;

    public class Main {
        public static void main(String[] args) {
            String jdbcUrl = "jdbc:mysql://localhost:3306/mydb";
            Connection connection = null;
            try {
                connection = DriverManager.getConnection(jdbcUrl, "root", "12345");
                System.out.println("Successfully connected to the database.");
            } catch (SQLException e) {
                System.out.println("Could not connect to the database.");
                e.printStackTrace();
            }

            try {
                Statement statement = connection.createStatement();
                String sql = "SELECT * FROM users WHERE username='" + args[0] + "'";
                ResultSet resultSet = statement.executeQuery(sql);
                if (resultSet.next()) {
                    System.out.println("Username exists in the database.");
                } else {
                    System.out.println("Username does not exist in the database.");
                }
            } catch (SQLException e) {
                System.out.println("Could not execute query.");
                e.printStackTrace();
            }
        }
    }