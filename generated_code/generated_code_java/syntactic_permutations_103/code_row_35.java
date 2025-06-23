import java.io.File;
public class HelloWorld {
    public static void main(String[] args) {
        try {
            File myfile = new File("test.txt");
            RandomAccessFile raf = new RandomAccessFile (myfile, "rw");
            if (!myfile.exists()) {
                myfile.createNewFile();
            } else {
                throw new Exception("File already exists");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}