import java.io.*;
    import javax.servlet.http.*;
    import java.sql.*;
    import org.apache.commons.lang3.StringEscapeUtils;

    public class Login extends HttpServlet {
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            String username = StringEscapeUtils.escapeHtml4(request.getParameter("username"));
            String password = StringEscapeUtils.escapeHtml4(request.getParameter("password"));
            String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
            ResultSet results;
            try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");
                    Statement statement = connection.createStatement();) {
                results = statement.executeQuery(sql);
            } catch (SQLException e) {
                response.sendRedirect("/internal_server_error");
            }
            if (results.next()) {
                response.sendRedirect("/success");
            } else {
                response.sendRedirect("/cant_login");
            }
        }
    }