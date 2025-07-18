import java.io.File;
public class Main {
    public static void main(String[] args) {
        File myfile = new File("filename");
        try {
            int fd = open("filename", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
            System.out.println("File created successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}