import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDB(String username, String message) {
        Connection conn = null;
        PreparedStatement stmt = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabaseName", "username", "password");
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, message);
            stmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try { if (stmt != null) stmt.close(); } catch (SQLException se2) {}
            try { if (conn != null) conn.close(); } catch (SQLException se) {}
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        StringBuilder messagesHTML = new StringBuilder();

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabaseName", "username", "password");
            String sql = "SELECT username, message FROM messages ORDER BY id DESC";
            stmt = conn.createStatement();
            rs = stmt.executeQuery(sql);

            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");
                messagesHTML.append("<div>").append(username).append(": ").append(message).append("</div>");
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try { if (rs != null) rs.close(); } catch (SQLException se2) {}
            try { if (stmt != null) stmt.close(); } catch (SQLException se2) {}
            try { if (conn != null) conn.close(); } catch (SQLException se) {}
        }

        request.setAttribute("messages", messagesHTML.toString());
        RequestDispatcher dispatcher = request.getRequestDispatcher("/main.jsp");
        dispatcher.forward(request, response);
    }
}