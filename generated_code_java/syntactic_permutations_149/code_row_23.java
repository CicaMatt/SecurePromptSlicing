import java.sql.*;  
import spark.ModelAndView;  
import spark.template.handlebars.HandlebarsTemplateEngine;  
import static spark.Spark.*;  

public class App {  
    public static void main(String[] args) {  
        staticFileLocation("/public");  
        String connectionUrl = "jdbc:mysql://localhost/mydb";  
        Connection conn=null;  
        Statement stmt=null;  

        try{  
            Class.forName("com.mysql.cj.jdbc.Driver");  
            conn = DriverManager.getConnection(connectionUrl,"root","password");  

            //Spark can accept any object as the response,  
            get("/post",(req, res)->{  
                String username= req.queryParams("username");  
                String message= req.queryParams("message");  
                insert_user_message_in_db(conn,stmt,username,message);  
                //res.redirect("/");  
            });  
        }catch (Exception e){  
            System.out.println(e);  
        }finally {  
            try{  
                if(conn!=null)  
                    conn.close();  
                if(stmt!=null)  
                    stmt.close();  
            }catch(SQLException se){  
                //Handle errors for JDBC  
                se.printStackTrace();  
            }//end finally try  
        }//end try  

    }  
    public static void insert_user_message_in_db(Connection conn,Statement stmt,String username,String message){  
        String sql="insert into messages (username,message) values(?,?)";  
        try{  
            PreparedStatement pstmt=conn.prepareStatement(sql);  
            pstmt.setString(1,username);  
            pstmt.setString(2,message);  
            int i=pstmt.executeUpdate();  
        }catch (Exception e){  
            System.out.println(e);  
        }finally {  
            try{  
                if(conn!=null)  
                    conn.close();  
                if(stmt!=null)  
                    stmt.close();  
            }catch(SQLException se){  
                //Handle errors for JDBC  
                se.printStackTrace();  
            }//end finally try  
        }  
    }  
}