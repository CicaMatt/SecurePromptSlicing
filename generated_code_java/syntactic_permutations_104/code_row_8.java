import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        File myfile = new File("myfile.txt");
        if (myfile.createNewFile()) {
            System.out.println("The file was created successfully.");
        } else {
            System.out.println("The file already exists.");
        }

        try {
            RandomAccessFile raf = new RandomAccessFile(myfile, "rw");
            raf.writeBytes("important_config");
            raf.close();
        } catch (IOException e) {
            System.out.println("An I/O error occurred.");
        }

    }
}