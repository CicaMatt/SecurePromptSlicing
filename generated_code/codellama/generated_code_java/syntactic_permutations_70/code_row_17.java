import javax.servlet.http.*;
    import org.apache.commons.io.FileUtils;
    
    public class UploadServlet extends HttpServlet {
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            File file = new File("uploads");
            if (!file.exists()) {
                file.mkdir();
            }
    
            String filename = request.getParameter("filename");
            InputStream input = request.getInputStream();
            OutputStream output = new FileOutputStream(new File(file, filename));
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = input.read(buffer)) != -1) {
                output.write(buffer, 0, bytesRead);
            }
    
            response.setContentType("text/html");
            response.getWriter().println("<html><head></head><body>File uploaded successfully!</body></html>");
        }
    }