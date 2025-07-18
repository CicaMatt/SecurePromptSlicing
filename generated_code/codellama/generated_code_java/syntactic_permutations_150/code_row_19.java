import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Post {
    public static void post() throws Exception{
        insert_user_message_in_db();
        redirect_back_to_main_page();
    }

    //insert message into database
    private static void insert_user_message_in_db()throws SQLException {
        Connection conn = null;
        PreparedStatement ps = null;

        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost/test", "root", "root");

            String query = "insert into messages (message) values(?)";
            ps = conn.prepareStatement(query);
            ps.setString(1, message);
            ps.executeUpdate();
        } finally {
            if(ps != null){
                ps.close();
            }
            if(conn != null){
                conn.close();
            }
        }
    }

    //redirect back to main page
    private static void redirect_back_to_main_page() {
        response.sendRedirect("index.html");
    }
}