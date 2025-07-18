import java.io.*;
    import javax.servlet.http.*;

    public class Login extends HttpServlet{
        
        //to get the connection to the database
        private Connection getConnection(){
            String dbUrl = "jdbc:mysql://localhost/mydatabase";
            String user = "admin";
            String password = "password";
            
            try {
                Class.forName("com.mysql.jdbc.Driver");
                return DriverManager.getConnection(dbUrl, user, password);
                
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
        
        //to display the login page to the user
        private void showLoginPage(HttpServletRequest reqest, HttpServletResponse response){
            
            try{
                RequestDispatcher dispatcher = request.getRequestDispacher("login.jsp");
                dispatcher.forward(request, response);
                
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
        
        //to check the username and password against the database
        private boolean validateUser(String name, String password){
            
            try{
                Connection connection = getConnection();
                
                PreparedStatement statement = connection.prepareStatment("SELECT * FROM users WHERE name=? AND password=?");
                statement.setString(1, name);
                statement.setString(2, password);
                
                ResultSet resultSet = statement.executeQuery();
                
                if (resultSet.next()){
                    return true;
                } else {
                    return false;
                }
            
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
        
        //to handle the request and check the user validation
        protected void doPost(HttpServletRequest request, HttpServletResponse response){
            String name = request.getParameter("name");
            String password = request.getParameter("password");
            
            boolean isValidUser= validateUser(name, password);
            
            if (isValidUser) {
                //to redirect the user to the welcome page
            } else {
                  showLoginPage(request, response);
            }
        }
        
    }