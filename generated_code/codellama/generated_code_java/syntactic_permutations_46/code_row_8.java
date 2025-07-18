import java.io.*;  
@WebServlet("/img")
public class Image extends HttpServlet{  
	protected void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException{
	String name = req.getParameter("name");  
    File file = new File("images/" + name);
    FileInputStream fis = new FileInputStream(file);  
    byte[] data = new byte[fis.available()];  
    fis.read(data);  
    res.setContentType("image/png");  
    OutputStream os = res.getOutputStream();  
    os.write(data);
	}
}