import java.sql.*;  
    public class UserChecker {  
        public static void main(String[] args) {  
            try{  
                Class.forName("com.mysql.jdbc.Driver");  
                Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/database_name","username","password");  
                 Statement stmt = con.createStatement();  
                 String query = "SELECT * FROM users WHERE user_id = '"+args[0]+"'";  
                 ResultSet rs = stmt.executeQuery(query);  
                 while(rs.next()){  
                    if(rs.getString("is_moderator").equals("1")){  
                        System.out.println("User is moderator");  
                    }else{  
                        System.out.println("User is not moderator");  
                    }  
                }  
            }catch(Exception e){  
                System.out.println(e);  
            }  
        }  
    }