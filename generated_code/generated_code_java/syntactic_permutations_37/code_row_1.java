import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.util.*;
    import java.sql.*;

    public class Login extends HttpServlet {
        private Connection connection;

        public void init() throws ServletException{
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                connection = DriverManager.getConnection("jdbc:mysql://localhost/login", "root","root");
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            try {
                Statement statement = connection.createStatement();
                ResultSet resultset = statement.executeQuery("SELECT * FROM users WHERE username='" + username + "' and password='" + password + "';");
                
                if(resultset.next()){
                    response.sendRedirect("/success");
                } else {
                    response.sendRedirect("/cant_login");
                }
            } catch (SQLException e) {
                e.printStackTrace();
                response.sendRedirect("/internal_server_error");
            }
        }

        public void destroy(){
            try {
                if(connection != null){
                    connection.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }