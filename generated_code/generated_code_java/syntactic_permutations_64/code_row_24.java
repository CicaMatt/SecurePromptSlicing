import java.io.*; 
import java.util.*; 
import javax.servlet.http.*; 
import javax.servlet.annotation.*; 
import java.sql.*; 
import java.text.SimpleDateFormat; 
// import com.mysql.jdbc.Driver; 
public class upload_pdf extends HttpServlet { 
@Override protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException { 
resp.setContentType("text/html"); 
PrintWriter out = resp.getWriter(); 
// get the uploaded file 
FileItemFactory factory = new DiskFileItemFactory(); 
ServletFileUpload upload = new ServletFileUpload(factory); 
List items = null; 
try { 
items = upload.parseRequest(req); 
} catch (FileUploadException e) { 
e.printStackTrace(); 
} 
// iterate through the list of uploaded files 
Iterator itr = items.iterator(); 
while (itr.hasNext()) { 
FileItem item = (FileItem) itr.next(); 
if (!item.isFormField()) { 
String name = new File(item.getName()).getName(); 
String path = req.getServletContext().getRealPath("/"); 
File uploads = new File(path + "/uploads/" + name); 
// write the file to the server 
try { 
item.write(uploads); 
} catch (Exception e) { 
e.printStackTrace(); 
} 
// save the file path in the mysql database 
String url = "jdbc:mysql://localhost/db_name"; 
String user = "root"; 
String password = ""; 
String sql = "INSERT INTO uploads (filepath) VALUES ('" + uploads.getPath() + "')"; 
try { 
Class.forName("com.mysql.jdbc.Driver"); 
Connection conn = DriverManager.getConnection(url, user, password); 
Statement stmt = conn.createStatement(); 
stmt.executeUpdate(sql); 
} catch (Exception e) { 
e.printStackTrace(); 
} 
out.println("File successfully uploaded"); 
} 
} 
} 
}