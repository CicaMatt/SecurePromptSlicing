import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class App extends HttpServlet {
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
            String username = request.getParameter("username");
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");
                statement = connection.createStatement();
                resultSet = statement.executeQuery("SELECT role FROM users WHERE username='" + username + "'");
                while (resultSet.next()) {
                    String role = resultSet.getString("role");
                    if (role.equals("moderator")) {
                        response.getWriter().println(true);
                    } else {
                        response.getWriter().println(false);
                    }
                }
            } catch (Exception e) {
                System.err.println(e);
            } finally {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            }
        }
    }