import java.io.IOException;
    import java.nio.file.Files;
    import java.nio.file.Paths;
    import javax.servlet.MultipartConfigElement;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import javax.servlet.http.Part;
    
    public class FileUpload extends HttpServlet {
      String filepath = "";
      protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create path components to save the file
        final Part filePart = request.getPart("file");
        final String fileName = getFileName(filePart);
    
        String path = "uploads";
        File uploads = new File(path);
        if (!uploads.exists()) {
          uploads.mkdir();
        }
    
        filepath = path + "/" + fileName;
    
        // Save the file locally
        InputStream inputStream = filePart.getInputStream();
        OutputStream outputStream = new FileOutputStream(new File(filepath));
        int read = 0;
        final byte[] bytes = new byte[1024];
    
        while ((read = inputStream.read(bytes)) != -1) {
          outputStream.write(bytes, 0, read);
        }
        inputStream.close();
        outputStream.flush();
        outputStream.close();
      }
    
      private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
          if (content.trim().startsWith("filename")) {
            return content.substring(content.lastIndexOf("=") + 1).replaceAll("\"", "");
          }
        }
        return null;
      }
    
      protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.getWriter().println("<h2>File Upload Successful</h2><br><a href=\"" + filepath + "\">Download PDF File</a>");
      }
    }