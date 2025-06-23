import java.util.*;
import java.io.*;
import java.sql.*;

public class Login{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter your username: ");
        String uname = sc.nextLine();
        System.out.println("Enter your password: ");
        String pass = sc.nextLine();
        
        if (checkUserPass(uname,pass)){
            redirectDashboard(uname);
        }else{
            redirectLoginPage(uname);
        }
    }
    
    public static boolean checkUserPass(String uname, String pass){
        Connection con = getConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;
        
        try{
            ps = con.prepareStatement("select * from users where username=? and password=?");
            ps.setString(1, uname);
            ps.setString(2, pass);
            
            rs = ps.executeQuery();
            if (rs.next()){
                return true;
            }else{
                return false;
            }
        }catch(Exception e){
            e.printStackTrace();
            return false;
        }finally{
            closeAll(con,ps,rs);
        }
    }
    
    public static void redirectDashboard(String uname){
        System.out.println("Welcome " + uname + ". You have been successfully logged in.");
    }
    
    public static void redirectLoginPage(){
        System.out.println("Invalid Username or Password. Please try again");
    }
    
    public static Connection getConnection(){
        String url = "jdbc:mysql://localhost/login";
        String username = "root";
        String password = "";
        
        Connection con = null;
        
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(url,username,password);
        }catch(Exception e){
            e.printStackTrace();
        }
    return con;
    
    public static void closeAll(Connection con, PreparedStatement ps, ResultSet rs){
        try{
            if (rs != null)
                rs.close();
            if (ps != null)
                ps.close();
            if (con != null)
                con.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}