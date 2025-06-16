import java.util.*;
    import java.io.*;
    import java.net.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class Login extends HttpServlet{
        private String username;
        private String password;
        
        public void doPost(HttpServletRequest request, HttpServletResponse response) 
                                throws ServletException, IOException {
            username = request.getParameter("username");
            password = request.getParameter("password");
            
            if (username != null && password != null) {
                String url = "jdbc:mysql://localhost:3306/mydb";
                Connection conn = DriverManager.getConnection(url, "root", "root");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username = '" + 
                                                    username + "' AND password = '" + password + "'");
                                                    
                if (rs.next()) {
                    RequestDispatcher dispatcher = request.getRequestDispatcher("/home.html");
                    dispatcher.forward(request, response);
                } else {
                    RequestDispatcher dispatcher = request.getRequestDispatcher("/login.html");
                    dispatcher.forward(request, response);
                }
            }
        }
    }