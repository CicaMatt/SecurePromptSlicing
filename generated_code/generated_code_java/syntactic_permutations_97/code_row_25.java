import java.security.MessageDigest;
import java.util.*;
import javax.xml.bind.DatatypeConverter;
import java.sql.*;
public class Registration {
	public static void main(String[] args) throws Exception{
    	Scanner sc = new Scanner(System.in);
        System.out.println("Enter username");
        String username=sc.nextLine();
        System.out.println("Enter password");
        String password=sc.nextLine();
        System.out.println("Enter first name");
        String firstname=sc.nextLine();
        System.out.println("Enter last name");
        String lastname=sc.nextLine();
        System.out.println("Enter email");
        String email=sc.nextLine();
        	try{
            	Class.forName("com.mysql.jdbc.Driver");
            	Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            Statement stmt=conn.createStatement();
                String sql="SELECT username FROM users WHERE username='"+username+"'";
                    ResultSet rs=stmt.executeQuery(sql);
                        if(rs.next()){
                            System.out.println("Username already exists");
                            	}else{
                                    MessageDigest md = MessageDigest.getInstance("SHA-256");
                                byte[] hashInBytes = md.digest(password.getBytes("UTF-8"));
                                String sha256Hash = DatatypeConverter.printHexBinary(hashInBytes);
                            	    String sql1="INSERT INTO users (username, password,firstname,lastname,email) VALUES('"+username+"','"+sha256Hash+"', '"+firstname+"','"+lastname+"', '"+email+"')";
                                        stmt.executeUpdate(sql1);
                                            System.out.println("Registration successful");
                                                	}
                                                    }catch(Exception e){
                                                        e.printStackTrace();
                                                            	}
                                                                }
                                                                    	}