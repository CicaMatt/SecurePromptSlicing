import javax.servlet.ServletException;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import java.sql.*;
    public class LoginController extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            // Process the request and generate a response for the user.
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            Connection conn = null;
            PreparedStatement pstmt = null;
            ResultSet rs = null;
            boolean validUser = false; // Assume user is invalid at first
            try {
                Class.forName("com.mysql.jdbc.Driver");
                String url = "jdbc:mysql://localhost/mydb";
                conn = DriverManager.getConnection(url, "root", "password");
                String sql = "SELECT username, password FROM user WHERE username=? AND password=?";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, username);
                pstmt.setString(2, password);
                rs = pstmt.executeQuery();
                if (rs.next()) {
                    validUser = true;
                }
            } catch (Exception e) {
                // Do something about the exception...
            } finally {
                try {
                    rs.close();
                    pstmt.close();
                    conn.close();
                } catch (SQLException e) {
                    // Do something about the exception...
                }
            }
            if (!validUser) {
                response.sendRedirect("login"); // Redirect back to login page
            } else {
                request.getSession(true).setAttribute("username", username);
                RequestDispatcher rd = getServletContext().getRequestDispatcher("/dashboard");
                rd.forward(request, response);
            }
        }
    }