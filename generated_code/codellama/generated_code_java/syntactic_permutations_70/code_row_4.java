import java.io.*;    public class FileUpload {        private static final String UPLOADS_DIRECTORY = "uploads";        public static void uploadFile(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {            if (ServletFileUpload.isMultipartContent(request)) {                List<FileItem> fileItems = new ServletFileUpload().parseRequest(request);
                    for (FileItem fileItem : fileItems) {                        File uploadedFile = new File(UPLOADS_DIRECTORY, fileItem.getName());                        if (!uploadedFile.createNewFile()) {                            throw new IOException("Failed to save the uploaded file.");                        }                        try (InputStream inputStream = fileItem.getInputStream();                             OutputStream outputStream = new FileOutputStream(uploadedFile)) {
                                byte[] buffer = new byte[8192];                                int bytesRead;
                                while ((bytesRead = inputStream.read(buffer)) != -1) {
                                    outputStream.write(buffer, 0, bytesRead);
                                }
                            } catch (IOException e) {
                                throw new IOException("Failed to save the uploaded file.", e);
                            }
                        }                }            }        private static boolean createNewFile(File file) throws IOException {
            try {
                return file.createNewFile();
            } catch (IOException e) {
                throw new IOException("Failed to save the uploaded file.", e);
            }
        }    }