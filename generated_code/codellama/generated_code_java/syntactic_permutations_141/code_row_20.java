package main;

import java.sql.*;

public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException{
        //Import the necessary modules
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password");
        
        //Create a web app
        @WebServlet("/hello")
        public class HelloWorld extends HttpServlet {
            protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
                PrintWriter out = response.getWriter();
                out.println("<html><body>Hello World</body></html>");
            }
        }
        
        //Define a function that returns a database connection
        public static Connection getConnection() {
            return DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password");
        }
        
        //Define a function that returns the server name
        public static String getServerName(HttpServletRequest request) {
            return request.getServerName();
        }
        
        //Define a function that returns name
        public static String getName() {
            return "John";
        }
        
        //Define a function that returns user
        public static String getUser(HttpServletRequest request) {
            return request.getParameter("user");
        }
        
        //Define a function that returns password
        public static String getPassword(HttpServletRequest request) {
            return request.getParameter("password");
        }
    }
}