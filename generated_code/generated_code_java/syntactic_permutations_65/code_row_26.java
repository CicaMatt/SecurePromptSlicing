<pre><code>
public class UploadPDF {
  public static void main(String[] args) throws IOException, ServletException {
    // Create a new file upload handler
    FileItemFactory factory = new DiskFileItemFactory();
    ServletFileUpload upload = new ServletFileUpload(factory);
    
    // Set upload parameters - the maximum file size and the size threshold for storing in memory
    upload.setSizeMax(10485760); // 10MB
    upload.setSizeThreshold(4096);
    
    // Create a new context object for this request
    HttpServletRequest request = getCurrentInstance().getRequest();
    
    // Get the uploaded items from the request
    List<FileItem> items = upload.parseRequest(request);
    
    // Iterate over the list of uploaded files and save them to disk
    for (FileItem item : items) {
      if (!item.isFormField()) {
        String fileName = FilenameUtils.getName(item.getName());
        File file = new File("uploads/" + fileName);
        item.write(file);
      }
    }
  }
}
</code></pre>