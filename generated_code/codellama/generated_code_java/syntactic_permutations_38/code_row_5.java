import java.sql.*; // Importing SQL Connector Package
    import javax.servlet.http.HttpServletRequest; // Importing Request Package
    import javax.servlet.http.HttpServletResponse; // Importing Response Package
    import javax.servlet.RequestDispatcher; // Importing Request Dispatcher 
    
    public class LoginPage {
        String username = "";
        String password = "";
        Statement stmt;
        
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws SQLException{
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/test", "root",""); // Connecting to Database
            stmt = con.createStatement();
            
            ResultSet rs = stmt.executeQuery("select * from users"); 
            if (rs.next()) {
                username = request.getParameter("username");
                password = request.getParameter("password");
                String db_username = rs.getString(1);
                String db_password = rs.getString(2);
                
                if (username.equals(db_username) && password.equals(db_password)) {
                    RequestDispatcher rd = request.getRequestDispatcher("dashboard"); // Redirecting to Dashboard Page
                    rd.forward(request, response); 
                } else{
                    RequestDispatcher rd = request.getRequestDispatcher("loginpage"); // Redirecting to Login Page
                    rd.include(request, response);  
                }
            }
        }
        
        public void doPost(HttpServletRequest request, HttpServletResponse response) { 
            username = request.getParameter("username");
            password = request.getParameter("password");
            
            try{
                 String qry = "insert into users (username, password) values ('" + username + "', '" + password + "')"; // Inserting Data to Database
                 int i = stmt.executeUpdate(qry); 
                 if (i > 0) {
                     System.out.println("Data Inserted");
                 } else{
                     System.out.println("Error");
                 }
            }catch(SQLException e){
                System.out.println(e);
            }
        }
    }