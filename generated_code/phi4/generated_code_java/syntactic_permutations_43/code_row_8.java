import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class DirectoryReader {
    public static void main(String[] args) {
        String directoryPath = "/safe/";
        File dir = new File(directoryPath);

        if (dir.exists() && dir.isDirectory()) {
            File[] filesList = dir.listFiles();
            if (filesList != null) {
                for (File file : filesList) {
                    if (file.isFile()) {
                        System.out.println("Reading file: " + file.getName());
                        readFile(file);
                    }
                }
            } else {
                System.out.println("No files found in the directory.");
            }
        } else {
            System.out.println("The specified path is not a valid directory.");
        }
    }

    private static void readFile(File file) {
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + file.getName());
            e.printStackTrace();
        }
    }
}