import javax.servlet.*;
    import javax.servlet.http.*;
    import java.io.*;
    
    public class UploadForm extends HttpServlet {
        private static final long serialVersionUID = 1L;
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            int maxFileSize = 5000 * 1024;
            int maxMemSize = 5000 * 1024;
            File file ;
    
            // Verifies if the form is a multi-part one
            if (!ServletFileUpload.isMultipartContent(request)) {
                // If it is not, send an error message
                PrintWriter writer = response.getWriter();
                writer.println("Error: Form must has enctype=multipart/form-data.");
                writer.flush();
                return;
            }
    
            // Configures upload settings
            DiskFileItemFactory factory = new DiskFileItemFactory();
            // Sets memory threshold - beyond which files are stored in disk
            factory.setSizeThreshold(maxMemSize);
            // Sets temporary location to store files
            factory.setRepository(new File("C:\\temp"));
    
            // Create a new file upload handler
            ServletFileUpload upload = new ServletFileUpload(factory);
            
            // Set maximum file size to be uploaded.
            upload.setSizeMax( maxFileSize );
    
            try { 
                // Parses the request's content to extract form fields
                List<FileItem> formItems = upload.parseRequest(request);
    
                if (formItems != null && formItems.size() > 0) {
                    // Iterates over form's fields
                    for (FileItem item : formItems) {
                        // Processes only fields that are not form fields
                        if (!item.isFormField()) {
                            String fileName = new File(item.getName()).getName();
                            String filePath = "C:\\uploads\\" + fileName;
                            
                            file = new File(filePath);
                            // Save the file on disk
                            item.write(file);
                        }
                    }
                }
            } catch (Exception ex) {
                request.setAttribute("message", "ERROR: " + ex.getMessage());
            }
    
            getServletContext().getRequestDispatcher("/result.jsp").forward(request, response);
        }
    }