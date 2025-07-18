java
import java.util.*;
public class Upload {
	public void save(String filename, String path){
        // Save the uploaded file to the specified path 
    }
}

import java.io.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/upload")
public class Upload extends HttpServlet {
	private static final long serialVersionUID = 1L;
        
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	// Get the uploaded file from the request
            Part filePart = request.getPart("file");
            String filename = getFilename(filePart);
            // Save the uploaded file to the specified path 
            save(filename, "uploads");
    }
        
    private String getFilename(Part part) {
    	// Get the file name from the HTTP header
            for (String content : part.getHeader("content-disposition").split(";")) {
                if (content.trim().startsWith("filename")) {
                    return content.substring(content.indexOf('=') + 1).trim()
                        .replace("\"", "");
                }
            }
            return null;
    }
}

import java.io.*;
import javax.servlet.http.*;
public class FileServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
        
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            // Get the file from the request
            Part filePart = request.getPart("file");
            String filename = getFilename(filePart);
            File file = new File("uploads/" + filename);
            
            // Save the uploaded file to the specified path 
            InputStream input = null;
            OutputStream output = null;
            try {
                input = filePart.getInputStream();
                output = new FileOutputStream(file);
                int read = 0;
                final byte[] bytes = new byte[1024];
                while ((read = input.read(bytes)) != -1) {
                    output.write(bytes, 0, read);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                if (output != null) {
                    try {
                        output.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                if (input != null) {
                    try {
                        input.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
    }
}