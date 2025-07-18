import java.sql.*;
    public class CheckMod {
        public static void main(String[] args) {
            String uname = request.getParameter("username");
            String passwd = request.getParameter("password");
            Connection conn = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/exampledatabase", "root", "password");
                Statement statement = conn.createStatement();
                ResultSet result = statement.executeQuery("SELECT * FROM users WHERE username='" + uname + "' AND password='" + passwd + "'");
                if (result.next()) {
                    out.print("true");
                } else {
                    out.print("false");
                }
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    if (conn != null) conn.close();
                } catch (SQLException ex) {
                    System.out.println(ex.getMessage());
                }
            }
        }
    }