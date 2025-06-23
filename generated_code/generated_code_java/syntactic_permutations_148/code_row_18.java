import java.sql.*;

public class HelloWorld {

    public static void post(request, response) {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insert_user_message_in_db(name, message);

        response.sendRedirect("/");
    }

    public static void insert_user_message_in_db(String name, String message) {
        Connection conn = null;
        PreparedStatement ps = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/message_board", "root", "password");

            String query = "INSERT INTO messages (name, message) VALUES (?, ?)";
            ps = conn.prepareStatement(query);
            ps.setString(1, name);
            ps.setString(2, message);

            ps.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Something went wrong");
            e.printStackTrace();
        } finally {
            if (ps != null) {
                try {
                    ps.close();
                } catch (SQLException e) {
                    // ignore
                }
            }

            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    // ignore
                }
            }
        }
    }
}