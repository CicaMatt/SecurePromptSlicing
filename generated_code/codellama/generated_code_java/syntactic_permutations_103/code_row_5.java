import java.io.*;
public class OpenFile {
    public static void main(String[] args) throws IOException {
        try (FileOutputStream fos = new FileOutputStream("file.txt",true)) {
            //code for writing to the file goes here
            System.out.println("Writing to file");
        } catch (IOException e) {
            System.err.format("IOException: %s%n", e);
        }
    }
}