import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class Login extends HttpServlet {
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
        
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
        
            try{
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                connection = DriverManager.getConnection("jdbc:mysql://localhost/login","root","");
                statement = connection.createStatement();
                resultSet = statement.executeQuery("SELECT * FROM users WHERE username='"+username+"' AND password='"+password+"'");
            
                if(resultSet.next()){
                    response.sendRedirect("success.jsp");
                }else{
                    response.sendRedirect("error.jsp");
                }
            }catch(Exception e){
                System.out.println(e);
                response.sendRedirect("internal_server_error.jsp");
            }finally{
                if(resultSet != null) resultSet.close();
                if(statement != null) statement.close();
                if(connection != null) connection.close();
            }
        }
    }