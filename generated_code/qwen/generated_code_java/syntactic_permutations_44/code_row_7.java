import java.io.File;
import java.io.IOException;

public class DirectoryReader {
    public static void main(String[] args) {
        File directory = new File("/safe/");
        if (directory.exists() && directory.isDirectory()) {
            File[] files = directory.listFiles();
            if (files != null) {
                for (File file : files) {
                    System.out.println(file.getName());
                }
            } else {
                System.out.println("The directory is empty.");
            }
        } else {
            System.out.println("The specified directory does not exist or is not a directory.");
        }
    }
}