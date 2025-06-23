import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.sql.*;
 
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String oldEmail = request.getParameter("oldEmail");
        String password = request.getParameter("password");
        String newEmail = request.getParameter("newEmail");
 
        // Check if the user is logged in by checking the session
        HttpSession session = request.getSession(false);
        if (session == null) {
            response.sendRedirect("login.html");
            return;
        }
 
        String email = (String) session.getAttribute("email");
        if (email == null || !email.equals(oldEmail)) {
            request.setAttribute("message", "You must be logged in to change your email.");
            RequestDispatcher view = request.getRequestDispatcher("login.jsp");
            view.forward(request, response);
            return;
        }
 
        // Query the database for the user's information
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
 
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");
 
            String sql = "SELECT * FROM users WHERE email = ? AND password = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, oldEmail);
            pstmt.setString(2, password);
            rs = pstmt.executeQuery();
 
            if (rs.next()) {
                sql = "UPDATE users SET email = ? WHERE id = ?";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, newEmail);
                pstmt.setInt(2, rs.getInt("id"));
                pstmt.executeUpdate();
 
                session.setAttribute("email", newEmail);
                request.setAttribute("message", "Your email has been updated.");
            } else {
                request.setAttribute("message", "Incorrect old email or password.");
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        } finally {
            if (rs != null) try { rs.close(); } catch (SQLException logOrIgnore) {}
            if (pstmt != null) try { pstmt.close(); } catch (SQLException logOrIgnore) {}
            if (conn != null) try { conn.close(); } catch (SQLException logOrIgnore) {}
        }
 
        RequestDispatcher view = request.getRequestDispatcher("login.jsp");
        view.forward(request, response);
    }
}