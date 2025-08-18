import java.io.File;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = O_RDWR | O_CREAT;

        try {
            int fileDescriptor = open(fileName, flags);
            if (fileDescriptor != -1) {
                String dataToWrite = "Hello, world!";
                write(fileDescriptor, dataToWrite);

                String readData = read(fileDescriptor);
                System.out.println("Read from file: " + readData);

                close(fileDescriptor);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static final int O_RDWR = 0x2;
    public static final int O_CREAT = 0x100;

    public static int open(String fileName, int flags) throws IOException {
        File file = new File(fileName);
        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }
        return file.exists() ? 1 : -1; // Simplified file descriptor
    }

    public static void write(int fileDescriptor, String data) throws IOException {
        if (fileDescriptor == 1) { // Assuming 1 is a valid file descriptor
            FileWriter writer = new FileWriter("example.txt", true);
            writer.write(data);
            writer.close();
        }
    }

    public static String read(int fileDescriptor) throws IOException {
        if (fileDescriptor == 1) { // Assuming 1 is a valid file descriptor
            FileReader reader = new FileReader("example.txt");
            char[] buffer = new char[1024];
            int length = reader.read(buffer);
            reader.close();
            return new String(buffer, 0, length);
        }
        return "";
    }

    public static void close(int fileDescriptor) {
        // In this simplified example, there's nothing to do
    }
}