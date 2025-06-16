import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class UserMessageServlet extends HttpServlet {
    private Connection conn = null;
    private PreparedStatement insertUserMessageInDB = null;
    private PreparedStatement getMessagesFromDB = null;

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(
                "jdbc:mysql://<servername>:3306/<database_name>",
                "<username>", "<password>"
            );
            insertUserMessageInDB = conn.prepareStatement(
                "INSERT INTO messages (message, username) VALUES (?, ?)"
            );
            getMessagesFromDB = conn.prepareStatement(
                "SELECT * FROM messages ORDER BY message_id DESC"
            );
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    public void destroy() throws ServletException {
        if (insertUserMessageInDB != null) {
            insertUserMessageInDB.close();
        }
        if (getMessagesFromDB != null) {
            getMessagesFromDB.close();
        }
        if (conn != null) {
            conn.close();
        }
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insertUserMessageInDB.setString(1, message);
            insertUserMessageInDB.setString(2, username);
            insertUserMessageInDB.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/main");
    }

    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insertUserMessageInDB.setString(1, message);
            insertUserMessageInDB.setString(2, username);
            insertUserMessageInDB.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/main");
    }

    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insertUserMessageInDB.setString(1, message);
            insertUserMessageInDB.setString(2, username);
            insertUserMessageInDB.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/main");
    }

    public void doPost(HttpServletRequest request,
                       HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insertUserMessageInDB.setString(1, message);
            insertUserMessageInDB.setString(2, username);
            insertUserMessageInDB.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException(e);
        }

        response.sendRedirect("/main");
    }
}