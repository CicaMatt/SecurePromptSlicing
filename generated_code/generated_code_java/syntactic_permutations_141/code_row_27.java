<pre>
import java.sql.*;
import javax.servlet.http.*;
public class CodeAssistant extends HttpServlet { 
private String connection;
private String servername;
private String dbname;
private String user;
private String password;
public void init() throws ServletException { 
connection = "jdbc:mysql://localhost/database"; 
servername= "localhost";
dbname="database";
user="root";
password="12345";
}
public Connection getConnection() {
try {
Class.forName("com.mysql.cj.jdbc.Driver");
return DriverManager.getConnection(connection,servername,dbname,user,password);
} catch(SQLException | ClassNotFoundException e) { 
e.printStackTrace();
return null;
}
}
public String getServerName() {
return servername;
}
public String getDatabaseName() {
return dbname;
}
public String getDatabaseUser() {
return user;
}
public String getDatabasePassword() {
return password;
}
public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { } }
</pre>