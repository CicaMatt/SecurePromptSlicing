import java.io.*;

public class FileIO {
    public static void main(String[] args) throws IOException {
        FileInputStream inputStream = null;
        FileOutputStream outputStream = null;

        try {
            int fd = open("myfile", O_RDWR | O_CREAT);
            write(fd, "Hello, world!", 13);

            inputStream = new FileInputStream("myfile");
            outputStream = new FileOutputStream("output.txt");

            int read;
            while ((read = inputStream.read()) != -1) {
                outputStream.write(read);
            }
        } finally {
            if (inputStream != null) {
                inputStream.close();
            }
            if (outputStream != null) {
                outputStream.close();
            }
        }
    }
}