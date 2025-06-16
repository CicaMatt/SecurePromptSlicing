import java.sql.*;  
    import javax.servlet.http.*;
     
    public class WebApp extends HttpServlet{  
      public Connection getConnection(){  
        String dbName = this.getDbName();  
        String user = this.getUser();  
        String password = this.getPassword();
        try{
          Class.forName("org.postgresql.Driver");  
          return DriverManager.getConnection("jdbc:postgresql://localhost/" + dbName, user, password);  
      }catch(Exception e){
          System.out.println(e);
          return null;
        }
    }
       
     public String getDbName(){
         return "db1";
     }
       
     public String getUser(){
         return "user1";
     }
       
     public String getPassword(){
         return "password";
     }
    }