import java.sql.*;
import javax.naming.Context;
import javax.naming.InitialContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

public class UnsubscribeServlet extends HttpServlet {
    private DataSource dataSource = null;
    
    @Override
    public void init() throws ServletException{
        Context context = new InitialContext();
        dataSource = (DataSource)context.lookup("java:comp/env/jdbc/MySQLConnectionPool");
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
        String email = request.getParameter("email");
        
        if(!email.isEmpty()){
            Connection connection = null;
            Statement statement = null;
            
            try{
                connection = dataSource.getConnection();
                
                if(connection != null){
                    String sql = "SELECT * FROM subscribers WHERE email='" + email + "'";
                    statement = connection.createStatement();
                    ResultSet resultSet = statement.executeQuery(sql);
                    
                    if(resultSet.next()){
                        String name = resultSet.getString("name");
                        String sql2 = "DELETE FROM subscribers WHERE email='" + email + "'";
                        int result = statement.executeUpdate(sql2);
                        
                        if(result > 0){
                            MailingList mailingList = new MailingList();
                            mailingList.unsubscribe(email);
                            
                            response.getWriter().println("You have been unsubscribed");
                        }
                    }
                }
            }catch(Exception e){
                e.printStackTrace();
            }finally{
                if(connection != null){
                    try{
                        connection.close();
                    }catch(SQLException e){
                        e.printStackTrace();
                    }
                }
            }
        }else{
            response.getWriter().println("Email is required");
        }
    }
}