import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class Post extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
            String username = request.getParameter("username");
            String message = request.getParameter("message");
            insertUserMessageInDB(username, message);
            RequestDispatcher req = request.getRequestDispatcher("/index.html");
            req.forward(request, response);
        }
    
        private void insertUserMessageInDB(String username, String message){
            //Create a database connection
            Connection con = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                con = DriverManager.getConnection("URL", "root", "password");
    
                //Prepare insert statement
                String query = "insert into MESSAGES (USERNAME, MESSAGE) values (?, ?)";
                PreparedStatement ps = con.prepareStatement(query);
                
                //Bind the parameters
                ps.setString(1, username);
                ps.setString(2, message);
    
                //Execute insert
                ps.executeUpdate();
            } catch (SQLException | ClassNotFoundException ex) {
                Logger.getLogger(Post.class.getName()).log(Level.SEVERE, null, ex);
            }finally{
                if(con != null){
                    try {
                        con.close();
                    } catch (SQLException ex) {
                        Logger.getLogger(Post.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        }
    
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
            String username = request.getParameter("username");
            String message = request.getParameter("message");
            RequestDispatcher req = request.getRequestDispatcher("/index.html");
            req.forward(request, response);
        }
    }