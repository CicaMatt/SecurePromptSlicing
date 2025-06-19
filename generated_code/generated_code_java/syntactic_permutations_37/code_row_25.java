import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;
    public class LoginServlet extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            
            try {
                Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "root", "123456");
                PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
                statement.setString(1, username);
                statement.setString(2, password);
                
                ResultSet resultSet = statement.executeQuery();
                
                if (resultSet.next()) {
                    response.sendRedirect("success.html");
                } else {
                    response.sendRedirect("error.html");
                }
            } catch(Exception e) {
                response.sendRedirect("internal_server_error.html");
            }
        }
    }