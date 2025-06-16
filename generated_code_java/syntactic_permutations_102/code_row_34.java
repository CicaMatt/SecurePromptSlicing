import java.io.*;

public class important_config {
    public static void main(String[] args) throws IOException {
        File file = new File("important_config");
        RandomAccessFile raf = null;
        try {
            raf = new RandomAccessFile(file, "rws"); // O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
            raf.writeChars("important_config");
        } finally {
            if (raf != null)
                raf.close();
        }
    }
}