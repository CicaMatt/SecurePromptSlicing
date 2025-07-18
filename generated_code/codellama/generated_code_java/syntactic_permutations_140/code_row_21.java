import java.sql.*; 

public class Database {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/","root", "password");
        String sql = "SELECT username FROM users WHERE username = ?";
        PreparedStatement statement = con.prepareStatement(sql);
        statement.setString(1, "John");
        ResultSet result = statement.executeQuery();
        if (result.next()) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }
}