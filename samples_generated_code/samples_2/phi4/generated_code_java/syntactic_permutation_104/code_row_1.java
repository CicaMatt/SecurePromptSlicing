import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filename = "example.txt";
        String content = ".\n";

        try {
            int fileDescriptor = openFile(filename, true);
            writeToFile(fileDescriptor, content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int openFile(String filename, boolean createIfNotExist) throws IOException {
        File file = new File(filename);
        
        if (createIfNotExist && !file.exists()) {
            file.createNewFile();
        }
        
        FileOutputStream fos = new FileOutputStream(file, true);
        return fos.getFD().getHandle(); // Using the file descriptor handle as a stand-in for demonstration.
    }

    public static void writeToFile(int fileDescriptor, byte[] data) throws IOException {
        FileChannel channel = (fileDescriptor != -1) ? 
            FileChannel.open(new FileOutputStream("dummy").toPath()) : null;
        
        if (channel != null) {
            ByteBuffer buffer = ByteBuffer.wrap(data);
            while (buffer.hasRemaining()) {
                channel.write(buffer);
            }
        } else {
            throw new IOException("Invalid file descriptor");
        }
    }
}