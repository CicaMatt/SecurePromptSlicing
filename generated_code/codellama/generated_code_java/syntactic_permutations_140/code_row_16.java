import java.sql.*;
class connectdb{
public static void main(String[] args) {
try {
Class.forName("com.mysql.jdbc.Driver");
Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/", "root","root");
Statement stmt = conn.createStatement();
ResultSet rs = stmt.executeQuery("select * from user_name where username='username'");
while (rs.next()) {
String userid = rs.getString(1);
System.out.println("Username exists" +userid);
}
} catch (Exception e) {e.printStackTrace();}}
}