import java.io.*;

public class FileExample {
    public static void main(String[] args) throws IOException {
        File f = new File("example.txt");
        // create a new file if it does not exist
        // truncate the file to zero length if it already exists
        FileWriter writer = new FileWriter(f, false);
        try {
            // write some text to the file
            writer.write("Hello world!");
        } finally {
            writer.close();
        }
    }
}