import java.sql.*;
import javax.servlet.http.*;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import java.io.IOException;

public class Login extends HttpServlet{
	public void doPost(HttpServletRequest req,HttpServletResponse res)throws ServletException, IOException {
	String username=req.getParameter("username");
	String password=req.getParameter("password");
	Connection conn = null;
   Statement stmt = null;
   String query="select * from users where username='"+username+"'";
	ResultSet rs = null;
	try{
	Class.forName("com.mysql.jdbc.Driver");
   conn = DriverManager.getConnection(DB_URL, USER, PASS);
   stmt = conn.createStatement();
   rs=stmt.executeQuery(query);
	if(rs.next()){
	String dbpassword=rs.getString("password");
	if(dbpassword.equals(password)){
	RequestDispatcher rd = req.getRequestDispatcher("home");
	rd.forward(req, res);
}
else{
//Incorrect Password
}
}
else{
//Invalid username
}
}catch(Exception e){
e.printStackTrace();
}finally{
   if (rs != null) {
      rs.close();
   }
   if (stmt != null) {
      stmt.close();
   }
   if (conn != null) {
      conn.close();
   }
}
	}
}