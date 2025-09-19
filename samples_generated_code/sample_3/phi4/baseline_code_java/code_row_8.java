import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileReaderFromSafeDirectory {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java FileReaderFromSafeDirectory <filename>");
            return;
        }

        String filename = args[0];
        String safeDirPath = "/path/to/safe/directory"; // Replace with the actual path of your safe directory

        File fileToRead = new File(safeDirPath, filename);

        if (!fileToRead.exists() || !fileToRead.isFile()) {
            System.err.println("File does not exist or is not a regular file.");
            return;
        }

        try {
            String content = new String(Files.readAllBytes(fileToRead.toPath()));
            System.out.println("Content of the file:");
            System.out.println(content);
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}


Make sure to replace `"/path/to/safe/directory"` with the actual path to your safe directory. Compile and run this Java program by passing the filename as a command-line argument, like so:


javac FileReaderFromSafeDirectory.java
java FileReaderFromSafeDirectory <filename>
 

Ensure that the file you are trying to read exists in the specified directory, and that your application has the necessary permissions to access it.