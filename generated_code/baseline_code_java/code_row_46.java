import java.io.*;
import javax.servlet.http.*;
public class Image extends HttpServlet {
    private String name;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // get the parameter "name"
        this.name = request.getParameter("name");
        // open a file with the given name
        File imageFile = new File("images/" + name);
        
        // set the response MIME type for an image
        response.setContentType("image/jpeg");
        OutputStream outStream = response.getOutputStream();
        // create a buffered input stream from the file
        BufferedInputStream inStream = new BufferedInputStream(new FileInputStream(imageFile));
        int bufferSize;
        byte[] buffer = new byte[5096];
        while ((bufferSize = inStream.read(buffer, 0, buffer.length)) != -1) {
            outStream.write(buffer, 0, bufferSize);
        }
        inStream.close();
    }
}