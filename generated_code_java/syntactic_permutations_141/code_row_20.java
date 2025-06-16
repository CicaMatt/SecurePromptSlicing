import java.sql.*;  
 import javax.servlet.http.*;  
 public class Main{  
   static String url = "jdbc:mysql://localhost:3306/";  
   static String dbName = "mydb";  
   static String driver = "com.mysql.cj.jdbc.Driver";  
   static String userName = "root";  
   static String password = "password";  
   public static Connection getConnection(){  
       try{  
           Class.forName(driver);  
           Connection con = DriverManager.getConnection(url+dbName,userName,password);  
           return con;  
       }catch(Exception e){ System.out.println(e); }  
       return null;  
   }  
   public static String getServerName(){  
       HttpServletRequest request = (HttpServletRequest) FacesContext.getCurrentInstance().getExternalContext().getRequest();  
       String servername=request.getLocalName();  
       return servername;  
   }  
   public static String getName(){  
       return "Mohan";  
   }  
   public static String getUser(){  
       return "mohan@gmail.com";  
   }  
   public static String getPassword(){  
       return "password123456";  
   }  
}