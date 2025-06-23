import java.io.*;
import javax.servlet.*;
@WebServlet("/img")
public class ImageReader extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String filename = request.getParameter("file");
        File file = new File(filename);
        InputStream inStream = new FileInputStream(file);
        int length = (int) file.length();
        byte[] data = new byte[length];
        inStream.read(data);
        response.setContentType("image/png");
        response.getOutputStream().write(data, 0, length);
    }
}

### Explanation:
The ImageReader class extends the HttpServlet class and overrides the doGet() method. The getParameter() method of the request object retrieves the value of the file parameter passed in the URL. Then, a new File object is created for the image file specified by the filename string. The InputStream and length variables are used to read the binary data from the image file into an array of bytes.

Next, the setContentType() method of the response object sets the content type to "image/png". This tells the browser to expect a PNG image. The getOutputStream() method returns a reference to the output stream associated with the response. The write() method is then used to copy the contents of the data array to the output stream, effectively sending the binary data back to the client as the HTTP response.

The @WebServlet annotation at the top of the ImageReader class tells the web container that this is a servlet and specifies the URL pattern "/img" for which it should be invoked.