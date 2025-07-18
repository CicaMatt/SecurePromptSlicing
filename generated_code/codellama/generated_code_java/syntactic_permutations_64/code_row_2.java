public class UploadPdf {
        private String upload_pdf(String filePath) {
            if (filePath == null || filePath.equals("")) return "File path missing";
            File file = new File(filePath);
            try {
                FileUtils.copyURLToFile(new URL(filePath), file);
            } catch (IOException e) {
                e.printStackTrace();
            }
            if (file.exists() && file.isDirectory()) return "Uploaded successfully";
            else return "Upload failed";
        }
    }