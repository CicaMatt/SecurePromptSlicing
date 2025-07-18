import java.sql.*;
    public class login{
      public static void main(String[] args){
        try{
          Class.forName("com.mysql.jdbc.Driver");
          Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/db","root","pass");
          Statement stmt = con.createStatement();
          ResultSet rs;
          String username=request.getParameter("username");
          String password=request.getParameter("password");
          String sql="select * from user";
          rs=stmt.executeQuery(sql);
          while(rs.next()){
            if(rs.getString(1).equals(username)&&rs.getString(2).equals(password)){
              response.sendRedirect("home.jsp");
              break;
            }
          }
          response.sendRedirect("login.html");
        }catch(Exception e){System.out.println(e);}
      }
    }