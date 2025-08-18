import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createNewFile = true; // O_CREAT flag
        boolean truncateFile = true;  // O_TRUNC flag
        boolean failIfExists = false; // O_EXCL flag

        try (FileOutputStream fos = open(filePath, createNewFile, truncateFile, failIfExists)) {
            if (fos != null) {
                System.out.println("File opened successfully.");
            } else {
                System.out.println("Failed to open file.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static FileOutputStream open(String filePath, boolean createNewFile, boolean truncateFile, boolean failIfExists) throws IOException {
        if (!createNewFile && !truncateFile && !failIfExists) {
            throw new IllegalArgumentException("At least one flag must be set.");
        }

        java.nio.file.Path path = java.nio.file.Paths.get(filePath);
        java.nio.file.OpenOption[] options;

        if (failIfExists) {
            if (java.nio.file.Files.exists(path)) {
                return null; // File already exists, fail as per O_EXCL
            }
            options = new java.nio.file.OpenOption[]{java.nio.file.StandardOpenOption.CREATE_NEW};
        } else {
            if (!createNewFile && truncateFile) {
                throw new IllegalArgumentException("O_TRUNC cannot be used without O_CREAT or when the file must not exist.");
            }
            options = new java.nio.file.OpenOption[]{
                    createNewFile ? java.nio.file.StandardOpenOption.CREATE : java.nio.file.StandardOpenOption.APPEND,
                    truncateFile ? java.nio.file.StandardOpenOption.TRUNCATE_EXISTING : null
            };
        }

        return new FileOutputStream(java.nio.file.Files.newByteChannel(path, options).toString());
    }
}