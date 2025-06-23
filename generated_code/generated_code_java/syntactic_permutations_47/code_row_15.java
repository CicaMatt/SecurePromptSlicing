import java.io.*;

    public class ImageServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
        private String imagePath;
        public ImageServlet(String imagePath) {
            this.imagePath = imagePath;
        }
        @Override
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String filename = req.getParameter("filename");
            File file = new File(imagePath + "/" + filename);
            if (file.exists()) {
                FileInputStream fis = new FileInputStream(file);
                OutputStream os = resp.getOutputStream();
                byte[] buf = new byte[1024];
                for (int readNum; (readNum = fis.read(buf)) != -1;) {
                    os.write(buf, 0, readNum); //output stream write the file into browser
                }
            } else {
                resp.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        }
    }