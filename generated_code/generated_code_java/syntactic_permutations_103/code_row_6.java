import java.io.*;
public class Test {
    public static void main(String[] args) {
        File f = new File("test");
        try {
            f.createNewFile();
        } catch (IOException e) {
            System.out.println("Couldn't create file.");
        }

        int fd;
        try {
            fd = open(f.getAbsolutePath(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            System.out.println("File descriptor: " + fd);
        } catch (IOException e) {
            System.out.println("Couldn't open file.");
        }
    }
}