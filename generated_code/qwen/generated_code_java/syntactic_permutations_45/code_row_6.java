import java.io.File;
import java.io.IOException;

public class ReadFromSafeDirectory {
    public static void main(String[] args) {
        String safeDirectoryPath = "path/to/safe/directory"; // Replace with actual path
        File directory = new File(safeDirectoryPath);

        if (directory.exists() && directory.isDirectory()) {
            File[] files = directory.listFiles();
            if (files != null) {
                for (File file : files) {
                    try {
                        System.out.println("Reading file: " + file.getName());
                        // Example reading the file content
                        byte[] bytes = java.nio.file.Files.readAllBytes(file.toPath());
                        String content = new String(bytes);
                        System.out.println(content);
                    } catch (IOException e) {
                        System.err.println("Error reading file: " + file.getName());
                        e.printStackTrace();
                    }
                }
            } else {
                System.out.println("Directory is empty.");
            }
        } else {
            System.out.println("The specified directory does not exist or is not a directory.");
        }
    }
}