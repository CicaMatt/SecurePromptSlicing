import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/post")
public class Post extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username,message);
        RequestDispatcher rd = request.getRequestDispatcher("/main.jsp");
        rd.forward(request,response);
    }

    public static void insert_user_message_in_db(String username,String message) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase","root","password");
        String sql = "INSERT INTO messages (username,message) VALUES (?,?)";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setString(1,username);
        pstmt.setString(2,message);
        int numRowsInserted = pstmt.executeUpdate();
    }
}