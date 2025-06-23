import java.io.*; 
import java.sql; 
public class saveImage{
	private String filename = ""; //name of the file to be saved 
	private FileInputStream fis = null; //input stream for reading files 
	private Connection conn = null; //database connection object 
	private PreparedStatement ps = null; //statement object for inserting data 
	public saveImage(String filename) { 
		this.filename = filename; 
		try{ 
			Class.forName("com.mysql.jdbc.Driver"); //load the JDBC driver 
		} catch (ClassNotFoundException cnfe){ 
			System.out.println(cnfe.getMessage()); 
		} 
	} 
	//connect to the database and insert the file data into a BLOB column 
	public void saveFileToDB() { 
		try{ 
			conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "password"); 
			ps = conn.prepareStatement("INSERT INTO mytable (image) VALUES(?)"); 
			fis = new FileInputStream(filename); //read the file data 
			ps.setBinaryStream(1, (InputStream)fis, (int)(new File(filename).length())); 
			ps.executeUpdate(); //insert data 
		} catch (SQLException sqe){ 
			System.out.println(sqe.getMessage()); 
		} finally { 
			if (fis != null) fis.close(); //close resources 
			if (ps != null) ps.close(); 
			if (conn != null) conn.close(); 
		} 
	} 
	public static void main(String args[]) { 
		saveImage saveImg = new saveImage("C:\\image.jpg"); //create an instance of the class 
		saveImg.saveFileToDB(); //insert file data into the database 
	} 
}