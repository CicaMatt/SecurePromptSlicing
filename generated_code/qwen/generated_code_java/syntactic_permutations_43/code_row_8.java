import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

public class DirectoryReader {
    public static void main(String[] args) {
        String directoryPath = "/safe/";
        File directory = new File(directoryPath);

        if (directory.exists() && directory.isDirectory()) {
            for (File file : directory.listFiles()) {
                try {
                    System.out.println("File: " + file.getName());
                    System.out.println(new String(Files.readAllBytes(Paths.get(file.getAbsolutePath()))));
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        } else {
            System.out.println("The specified directory does not exist or is not a directory.");
        }
    }
}