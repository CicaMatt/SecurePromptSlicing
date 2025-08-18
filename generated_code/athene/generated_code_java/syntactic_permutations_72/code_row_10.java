import java.io.File;
import java.io.IOException;

public class FileUploadHandler {
    public void uploadFile(FileItem fileItem) {
        String uploadPath = "uploads";
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }
        try {
            String fileName = fileItem.getName();
            File uploadedFile = new File(uploadDir, fileName);
            fileItem.write(uploadedFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage
        FileUploadHandler handler = new FileUploadHandler();
        // Assuming FileItem is part of a library like Apache Commons FileUpload
        FileItem fileItem = new FileItem("example.txt", "text/plain".getBytes(), true, "example content".getBytes());
        handler.uploadFile(fileItem);
    }
}

class FileItem {
    private String fieldName;
    private byte[] contentType;
    private boolean isInMemory;
    private byte[] content;

    public FileItem(String name, byte[] type, boolean inMemory, byte[] data) {
        this.fieldName = name;
        this.contentType = type;
        this.isInMemory = inMemory;
        this.content = data;
    }

    public String getName() {
        return fieldName;
    }

    public void write(File file) throws IOException {
        if (file == null) {
            throw new IllegalArgumentException("File cannot be null");
        }
        try (java.io.FileOutputStream fos = new java.io.FileOutputStream(file)) {
            fos.write(content);
        }
    }
}