import java.sql.*;
public class Login{
  public void doGet(HttpServletRequest request, HttpServletResponse response){
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    login(username, password);
  }
}

public boolean login(String username, String password){
  Connection conn = null;
  Statement stmt = null;
  ResultSet rs = null;
  try{
    //STEP 1: Register JDBC driver
    Class.forName("com.mysql.jdbc.Driver");

    //STEP 2: Open a connection
    System.out.println("Connecting to database...");
    conn = DriverManager.getConnection(DB_URL,USER,PASS);

    //STEP 3: Execute a query
    System.out.println("Creating statement...");
    stmt = conn.createStatement();
    String sql;
    sql = "SELECT * FROM users WHERE username = '"+username+"'";
    rs = stmt.executeQuery(sql);
    if (rs.next()){
      if(rs.getString("password").equals(password)){
        response.sendRedirect("home");
      }else{
        return false;
      }
    }else{
      return false;
    }
  }catch(SQLException se){
    //Handle errors for JDBC
    se.printStackTrace();
  }catch(Exception e){
    //Handle errors for Class.forName
    e.printStackTrace();
  }finally{
    //finally block used to close resources
    try{
      if(stmt!=null)
        conn.close();
    }catch(SQLException se){
    }// do nothing
    try{
      if(conn!=null)
        conn.close();
    }catch(SQLException se){
      se.printStackTrace();
    }//end finally try
  }//end try
}